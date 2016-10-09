/*
 * file: mobility.c
 * created: 20161008
 * author(s): mr-augustine
 *
 * Defines the functions used to initialize and control the steering servo and
 * drive motor.
 */
 #include <util/delay.h>
 #include <avr/io.h>

 #include "mobility.h"
 #include "pins.h"
 // #include "statevars.h"

 typedef enum {
   Gear_Forward,
   Gear_Pre_Reverse,
   Gear_Reverse,
   Gear_Neutral
 } Drive_Gear;

static uint16_t mobility_throttle_us;
static uint16_t mobility_steer_us;

const uint32_t ticks_per_period = PRESCALED_TICKS_PER_SEC /
                              (MILLISEC_PER_SEC / PWM_PERIOD_MS);
const uint32_t us_per_period = MICROSEC_PER_MILLISEC * PWM_PERIOD_MS;

Drive_Gear current_gear;

//TODO change this to match the user-defined PWM period
static void tnp_bypass(uint16_t iterations) {
  uint16_t pulse_on_duration_us = 1500;
  uint16_t pulse_off_duration_us = 23500;

  uint8_t pulse_iterations = iterations;
  uint8_t i;

  // Ensure the drive and steering pins are initially low
  THROTTLE_PORT &= ~(1 << THROTTLE_PIN);
  STEERING_PORT &= ~(1 << STEERING_PIN);

  for (i = 0; i < pulse_iterations; i++) {
    // Start the neutral pwm pulses
    THROTTLE_PORT |= (1 << THROTTLE_PIN);
    STEERING_PORT |= (1 << STEERING_PIN);

    // Hold the pulse
    _delay_us(pulse_on_duration_us);

    // end the pulse
    THROTTLE_PORT &= ~(1 << THROTTLE_PIN);
    STEERING_PORT &= ~(1 << STEERING_PIN);
    _delay_us(pulse_off_duration_us);
  }

  return;
}

static uint16_t pwm_to_ticks(uint16_t pwm_us) {
  return (ticks_per_period * pwm_us) / us_per_period;
}

uint8_t init_mobility(void) {
  int pwm_period_ms = 20;
  int us_per_period = 1000 * pwm_period_ms; // 1000 us/ms * ms/pd = us/pd
  int desired_pwm_us = 1500;

  pinMode(3, 1);

  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3  = 0;

  // Setting up Fast PWM where TOP == OCRnA, Update happens at BOTTOM,
  // and Timer Overflow Flag is set at TOP (see Table 17-2)
  TCCR3A |= (1 << WGM30) | (1 << WGM31);
  TCCR3B |= (1 << WGM32) | (1 << WGM33);

  // Clear the ESC pin when the output compare register matches (see Table 17-4)
  TCCR3A |= (1 << COM3C1);

  // Setting 64 prescaler; CSn1 = 1 and CSn0 = 1 (see Table 17-6)
  // 250,000 ticks per second
  TCCR3B |= (1 << CS30) | (1 << CS31);

  // Setting output compare register to turn signal LOW at desired width
  uint32_t ticks_per_period = PRESCALED_TICKS_PER_SEC / (MILLISEC_PER_SEC / pwm_period_ms);
  uint32_t desired_width_ticks = (ticks_per_period * desired_pwm_us) / us_per_period;
  OCR3A = ticks_per_period;
  OCR3C = desired_width_ticks;

  return 1;
}

uint8_t mobility_init(void) {
  // current_gear = Gear_Neutral;
  mobility_throttle_us = SPEED_NEUTRAL;
  mobility_steer_us = TURN_NEUTRAL;

  THROTTLE_PORT = 0;
  STEERING_PORT = 0;

  THROTTLE_DDR |= (1 << THROTTLE_PIN);
  STEERING_DDR |= (1 << STEERING_PIN);
  // pinMode(3, 1);
  // pinMode(2, 1);

  // TODO define these registers in pins.h as THROTTLE/STEERING_TCCR[AB]
  // and THROTTLE/STEERING_TIMER
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;

  // Specify Fast PWM on Timer 3 (see Table 17-2)
  TCCR3A |= (1 << WGM30) | (1 << WGM31);
  TCCR3B |= (1 << WGM32) | (1 << WGM33);

  // Clear the steering and throttle pins when the output compare register
  // matches, COM3C1 for throttle, COM3B1 for steering  (see Table 17-4)
  // TODO define these constants in pins.h as THROTTLE/STEERING_COMPARE_ENABLE_PIN
  TCCR3A |= (1 << COM3C1) | (1 << COM3B1);

  // Set the prescaler to 64 (see Table 17-6)
  TCCR3B |= PRESCALER_64;

  // Set the TOP value
  MOBILITY_COMPARE_REG = ticks_per_period;

  // Set the output compare register value that would cause the PWM signal to
  // turn LOW at the desired width
  // uint16_t desired_steer_width_ticks = pwm_to_ticks(mobility_steer_us);
  // uint16_t desired_throttle_width_ticks = pwm_to_ticks(mobility_throttle_us);

  // STEERING_COMPARE_REG = desired_steer_width_ticks;
  // THROTTLE_COMPARE_REG = desired_throttle_width_ticks;

  // Begin Throttle Neutral Protection bypass
  //tnp_bypass(TNP_MIN_ITERATIONS);

  THROTTLE_COMPARE_REG = pwm_to_ticks(mobility_throttle_us);
  STEERING_COMPARE_REG = pwm_to_ticks(mobility_steer_us);
  //mobility_stop();
  //mobility_steer(TURN_NEUTRAL);

  return 1;
}

void mobility_stop(void) {
  switch (current_gear) {

    // If you're already in neutral
    case Gear_Neutral:
      mobility_throttle_us = SPEED_NEUTRAL;
      break;

    // If you're currently driving forward and want to stop, decrease the PWM signal
    // by a certain amount for this iteration. Continue doing so for subsequent
    // iterations until the PWM width equals 1500. Then change the current_gear
    // to Gear_Neutral.
    case Gear_Forward:
      if (mobility_throttle_us > SPEED_NEUTRAL) {
        mobility_throttle_us -= FWD_TO_STOP_RATE_US;
      } else {
        mobility_throttle_us = SPEED_NEUTRAL;
        current_gear = Gear_Neutral;
      }
      break;

    // Likewise, if you're currently driving in reverse and want to stop, increase
    // the PWM signal by a certain amount for this iteration. Continue doing so
    // until the PWM width equals 1500. Then change the current_gear to
    // Gear_Neutral.
    case Gear_Reverse:
      if (mobility_throttle_us < SPEED_NEUTRAL) {
        mobility_throttle_us += REV_TO_STOP_RATE_US;
      } else {
        mobility_throttle_us = SPEED_NEUTRAL;
        current_gear = Gear_Neutral;
      }
      break;

    default:
      // TODO consider reporting an error in this case
      ;
  }

  THROTTLE_COMPARE_REG = pwm_to_ticks(mobility_throttle_us);

  // statevars.mobility_motor_pwm = THROTTLE_COMPARE_REG;

  return;
}

void mobility_steer(uint16_t steer_pwm) {
  // Steering values greater than 1500 will steer Left. And steering values
  // less than 1500 will steer Right. This code snippet prevents the
  // steering servo from getting a signal that would command it beyond its
  // turn limits.
  if (steer_pwm < TURN_FULL_RIGHT) {
    steer_pwm = TURN_FULL_RIGHT;
  }

  if (steer_pwm > TURN_FULL_LEFT) {
    steer_pwm = TURN_FULL_LEFT;
  }

  mobility_steer_us = steer_pwm;

  STEERING_COMPARE_REG = pwm_to_ticks(mobility_steer_us);

  // statevars.mobility_steering_pwm = STEERING_COMPARE_REG;

  return;
}
