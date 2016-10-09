/*
 * file: mobility.h
 * created: 20161008
 * author(s): mr-augustine
 *
 * Lists the functions used to initialize and control the steering servo and
 * drive motor. This time we're using PWM mode and not Interrupt Service Routines.
 *
 * The extern "C" construct allows the main Arduino program to use the
 * functions declared below.
 */
#ifndef _MOBILITY_H_
#define _MOBILITY_H_

#define PWM_PERIOD_MS         20
#define MILLISEC_PER_SEC      1000
#define MICROSEC_PER_MILLISEC 1000
#define PRESCALER_64          ((1 << CS30) | (1 << CS31))
#define PRESCALED_TICKS_PER_SEC 250000

#define MOBILITY_COMPARE_REG  OCR3A
#define STEERING_COMPARE_REG  OCR3B
#define THROTTLE_COMPARE_REG  OCR3C

#define FWD_ACCEL_RATE_US     100
#define FWD_TO_STOP_RATE_US   100
#define REV_TO_STOP_RATE_US   100
#define REV_RATE_US           10
#define PRE_REV_STOP_US       1400
#define PRE_REV_HOLD_ITERS    40
#define TNP_MIN_ITERATIONS    100   // minimum number of iterations to execute
                                    // throttle neutral protection bypass

#define SPEED_FWD_CREEP       1600
#define SPEED_FWD_CRUISE      1800
#define SPEED_FWD_LUDICROUS   2000
#define SPEED_NEUTRAL         1500
#define SPEED_REV_CREEP       1400
#define SPEED_REV_CRUISE      1200
#define SPEED_REV_LUDICROUS   1100
#define TURN_FULL_LEFT        1900
#define TURN_FULL_RIGHT       1100
#define TURN_NEUTRAL          1500

typedef enum {
  Speed_Creep,
  Speed_Cruise,
  Speed_Ludicrous
} Drive_Speed;

#ifdef __cplusplus
extern "C" {
  uint8_t mobility_init(void);
  uint8_t init_mobility(void);
  void mobility_start_control_output(void);
  void mobility_drive_fwd(Drive_Speed speed);
  void mobility_drive_rev(Drive_Speed speed);
  void mobility_hardstop(void);
  void mobility_blocking_stop(void);
  void mobility_stop(void);
  void mobility_steer(uint16_t steer_pwm);
}
#endif // #ifdef __cplusplus

#endif // #ifndef _MOBILITY_H_
