#include "Mobility.h"

uint8_t Mobility::initialize(void) {
  THROTTLE_PORT = 0;
  STEERING_PORT = 0;

  THROTTLE_DDR |= (1 << THROTTLE_DDR_PIN);
  STEERING_DDR |= (1 << STEERING_DDR_PIN);

  // Even though the steering and throttle pins will most likely be
  // attached to the same timer, we'll handle them separately just in
  // case we decide to put them on separate timers later.
  MOBILITY_TCCRA = 0;
  MOBILITY_TCCRB = 0;
  MOBILITY_TIMER = 0;

  // Specify Fast PWM (see Table 17-2)
  MOBILITY_TCCRA |= (1 << WGM30) | (1 << WGM31);
  MOBILITY_TCCRB |= (1 << WGM32) | (1 << WGM33);

  // Clear the steering and throttle pins when the output compare register
  // matches
  MOBILITY_TCCRB |= STEERING_COMP_MODE | THROTTLE_COMP_MODE;

  // Set the prescaler (see Table 17-6)
  MOBILITY_TCCRB |= PRESCALER_64;

  // Set the TOP values
  MOBILITY_TOP = ticks_per_period;

  STEERING_COMPARE_REG = pwm_to_ticks(steering_us);
  THROTTLE_COMPARE_REG = pwm_to_ticks(throttle_us);

  tnp_bypass();

  return 1;
}

uint16_t Mobility::pwm_to_ticks(uint16_t pwm_us) {
  return (ticks_per_period * pwm_us) / microsec_per_period;
}

void Mobility::steer(uint16_t steer_pwm) {
  // Steering values greater than 1500 will steer Left. And steering values
  // less than 1500 will steer Right. This code snippet prevents the
  // steering servo from getting a signal that would command it beyond its
  // turn limits.
  if (steer_pwm < STEER_FULL_RIGHT) {
    steer_pwm = STEER_FULL_RIGHT;
  }

  if (steer_pwm > STEER_FULL_LEFT) {
    steer_pwm = STEER_FULL_LEFT;
  }

  steering_us = steer_pwm;

  STEERING_COMPARE_REG = pwm_to_ticks(steering_us);

  // statevars.mobility_steering_pwm = STEERING_COMPARE_REG;

  return;
}

void Mobility::stop(void) {
  switch (current_gear) {
    case DriveGear_Neutral:
      throttle_us = THROT_NEUTRAL;
      break;

    // If you're currently driving forward and want to stop, decrease the PWM signal
    // by a certain amount for this iteration. Continue doing so for subsequent
    // iterations until the PWM width equals 1500. Then change the current_gear
    // to Gear_Neutral.
    case DriveGear_Forward:
      if (throttle_us > THROT_NEUTRAL) {
        throttle_us -= FWD_TO_STOP_RATE_US;
      } else {
        throttle_us = THROT_NEUTRAL;
        current_gear = DriveGear_Neutral;
      }
      break;

    // Likewise, if you're currently driving in reverse and want to stop, increase
    // the PWM signal by a certain amount for this iteration. Continue doing so
    // until the PWM width equals 1500. Then change the current_gear to
    // Gear_Neutral.
    case DriveGear_Reverse:
      if (throttle_us < THROT_NEUTRAL) {
        throttle_us += REV_TO_STOP_RATE_US;
      } else {
        throttle_us = THROT_NEUTRAL;
        current_gear = DriveGear_Neutral;
      }
      break;

    default:
      // TODO consider reporting an error in this case
      ;
  }

  THROTTLE_COMPARE_REG = pwm_to_ticks(throttle_us);

  // statevars.mobility_throttle_us = THROTTLE_COMPARE_REG;

  return;
}
