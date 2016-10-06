#include <stdint.h>
#include "Statevars.h"

#define PASS "[PASS] "
#define FAIL "[FAIL] "

void setup() {
  Statevars my_vars;

  Serial.begin(9600);
  test_reset(my_vars);
  test_setters(my_vars);
}

void loop() {
  // Nothing needs to looped
}

void test_reset(Statevars& s) {
  s.reset();

  Serial.println("[TEST] reset() should set all values to zero; prefix and suffix should be the default values");

  Serial.print(s.get_prefix() == 0xDADAFEED ? PASS : FAIL);
  Serial.print("prefix = ");
  Serial.println(s.get_prefix(), HEX);

  Serial.print(s.get_status() == 0 ? PASS : FAIL);
  Serial.print("status = ");
  Serial.println(s.get_status());

  Serial.print(s.get_main_loop_counter() == 0 ? PASS : FAIL);
  Serial.print("main_loop_counter = ");
  Serial.println(s.get_main_loop_counter());

  Serial.print(s.get_gps_lat_deg() == 0 ? PASS : FAIL);
  Serial.print("gps_lat_deg = ");
  Serial.println(s.get_gps_lat_deg());

  Serial.print(s.get_gps_lat_ddeg() == 0.0 ? PASS : FAIL);
  Serial.print("gps_lat_ddeg = ");
  Serial.println(s.get_gps_lat_ddeg());

  Serial.print(s.get_gps_long_deg() == 0 ? PASS : FAIL);
  Serial.print("gps_long_deg = ");
  Serial.println(s.get_gps_long_deg());

  Serial.print(s.get_gps_long_ddeg() == 0.0 ? PASS : FAIL);
  Serial.print("gps_long_ddeg = ");
  Serial.println(s.get_gps_long_ddeg());

  Serial.print(s.get_gps_hdop() == 0.0 ? PASS : FAIL);
  Serial.print("gps_hdop = ");
  Serial.println(s.get_gps_hdop());

  Serial.print(s.get_gps_ground_course_deg() == 0.0 ? PASS : FAIL);
  Serial.print("gps_ground_course_deg = ");
  Serial.println(s.get_gps_ground_course_deg());

  Serial.print(s.get_gps_ground_speed_kt() == 0.0 ? PASS : FAIL);
  Serial.print("gps_ground_speed_kt = ");
  Serial.println(s.get_gps_ground_speed_kt());

  Serial.print(s.get_gps_satcount() == 0 ? PASS : FAIL);
  Serial.print("gps_satcount = ");
  Serial.println(s.get_gps_satcount());

  Serial.print(s.get_heading_raw() == 0 ? PASS : FAIL);
  Serial.print("heading_raw = ");
  Serial.println(s.get_heading_raw());

  Serial.print(s.get_heading_deg() == 0.0 ? PASS : FAIL);
  Serial.print("heading_deg = ");
  Serial.println(s.get_heading_deg());

  Serial.print(s.get_pitch_deg() == 0 ? PASS : FAIL);
  Serial.print("pitch_deg = ");
  Serial.println(s.get_pitch_deg());

  Serial.print(s.get_roll_deg() == 0 ? PASS : FAIL);
  Serial.print("roll_deg = ");
  Serial.println(s.get_roll_deg());

  Serial.print(s.get_odometer_ticks() == 0 ? PASS : FAIL);
  Serial.print("odometer_ticks = ");
  Serial.println(s.get_odometer_ticks());

  Serial.print(s.get_odometer_timestamp() == 0 ? PASS : FAIL);
  Serial.print("odometer_timestamp = ");
  Serial.println(s.get_odometer_timestamp());

  Serial.print(s.get_odometer_ticks_are_fwd() == 0 ? PASS : FAIL);
  Serial.print("odometer_ticks_are_fwd = ");
  Serial.println(s.get_odometer_ticks_are_fwd());

  Serial.print(s.get_nav_heading_deg() == 0.0 ? PASS : FAIL);
  Serial.print("nav_heading_deg = ");
  Serial.println(s.get_nav_heading_deg());

  Serial.print(s.get_nav_gps_heading() == 0.0 ? PASS : FAIL);
  Serial.print("nav_gps_heading = ");
  Serial.println(s.get_nav_gps_heading());

  Serial.print(s.get_nav_latitude() == 0.0 ? PASS : FAIL);
  Serial.print("nav_latitude = ");
  Serial.println(s.get_nav_latitude());

  Serial.print(s.get_nav_longitude() == 0.0 ? PASS : FAIL);
  Serial.print("nav_longitude = ");
  Serial.println(s.get_nav_longitude());

  Serial.print(s.get_nav_waypt_latitude() == 0.0 ? PASS : FAIL);
  Serial.print("nav_waypt_latitude = ");
  Serial.println(s.get_nav_waypt_latitude());

  Serial.print(s.get_nav_waypt_longitude() == 0.0 ? PASS : FAIL);
  Serial.print("nav_waypt_longitude = ");
  Serial.println(s.get_nav_waypt_longitude());

  Serial.print(s.get_nav_rel_bearing_deg() == 0.0 ? PASS : FAIL);
  Serial.print("nav_rel_bearing_deg = ");
  Serial.println(s.get_nav_rel_bearing_deg());

  Serial.print(s.get_nav_distance_to_waypt_m() == 0.0 ? PASS : FAIL);
  Serial.print("nav_distance_to_waypt_m = ");
  Serial.println(s.get_nav_distance_to_waypt_m());

  Serial.print(s.get_nav_speed() == 0.0 ? PASS : FAIL);
  Serial.print("nav_speed = ");
  Serial.println(s.get_nav_speed());

  Serial.print(s.get_mobility_motor_pwm() == 0 ? PASS : FAIL);
  Serial.print("mobility_motor_pwm = ");
  Serial.println(s.get_mobility_motor_pwm());

  Serial.print(s.get_mobility_steering_pwm() == 0 ? PASS : FAIL);
  Serial.print("mobility_steering_pwm = ");
  Serial.println(s.get_mobility_steering_pwm());

  Serial.print(s.get_control_heading_desired() == 0.0 ? PASS : FAIL);
  Serial.print("control_heading_desired = ");
  Serial.println(s.get_control_heading_desired());

  Serial.print(s.get_control_xtrack_error() == 0.0 ? PASS : FAIL);
  Serial.print("control_xtrack_error = ");
  Serial.println(s.get_control_xtrack_error());

  Serial.print(s.get_control_xtrack_error_rate() == 0.0 ? PASS : FAIL);
  Serial.print("control_xtrack_error_rate = ");
  Serial.println(s.get_control_xtrack_error_rate());

  Serial.print(s.get_control_xtrack_error_sum() == 0.0 ? PASS : FAIL);
  Serial.print("control_xtrack_error_sum = ");
  Serial.println(s.get_control_xtrack_error_sum());

  Serial.print(s.get_control_steering_pwm() == 0.0 ? PASS : FAIL);
  Serial.print("control_steering_pwm = ");
  Serial.println(s.get_control_steering_pwm());

  Serial.print(s.get_suffix() == 0xCAFEBABE ? PASS : FAIL);
  Serial.print("suffix = ");
  Serial.println(s.get_suffix(), HEX);

  Serial.println("---- end of test ----");
}

void test_setters(Statevars& s) {
  float expected_float = 1.23;
  uint32_t expected_uint32_t = 4294967295;
  uint16_t expected_uint16_t = 32768;
  uint8_t expected_uint8_t = 255;
  int8_t expected_int8_t = -127;

  Serial.println("[TEST] setter functions should set the variables to the specified values");

  s.set_prefix(expected_uint32_t);
  Serial.print(s.get_prefix() == expected_uint32_t ? PASS : FAIL);
  Serial.print("prefix = ");
  Serial.println(s.get_prefix(), HEX);

  s.set_status(expected_uint32_t);
  Serial.print(s.get_status() == expected_uint32_t ? PASS : FAIL);
  Serial.print("status = ");
  Serial.println(s.get_status());

  s.set_main_loop_counter(expected_uint32_t);
  Serial.print(s.get_main_loop_counter() == expected_uint32_t ? PASS : FAIL);
  Serial.print("main_loop_counter = ");
  Serial.println(s.get_main_loop_counter());

  s.set_gps_lat_deg(expected_uint16_t);
  Serial.print(s.get_gps_lat_deg() == expected_uint16_t ? PASS : FAIL);
  Serial.print("gps_lat_deg = ");
  Serial.println(s.get_gps_lat_deg());

  s.set_gps_lat_ddeg(expected_float);
  Serial.print(s.get_gps_lat_ddeg() == expected_float ? PASS : FAIL);
  Serial.print("gps_lat_ddeg = ");
  Serial.println(s.get_gps_lat_ddeg());

  s.set_gps_long_deg(expected_uint16_t);
  Serial.print(s.get_gps_long_deg() == expected_uint16_t ? PASS : FAIL);
  Serial.print("gps_long_deg = ");
  Serial.println(s.get_gps_long_deg());

  s.set_gps_long_ddeg(expected_float);
  Serial.print(s.get_gps_long_ddeg() == expected_float ? PASS : FAIL);
  Serial.print("gps_long_ddeg = ");
  Serial.println(s.get_gps_long_ddeg());

  s.set_gps_hdop(expected_float);
  Serial.print(s.get_gps_hdop() == expected_float ? PASS : FAIL);
  Serial.print("gps_hdop = ");
  Serial.println(s.get_gps_hdop());

  s.set_gps_ground_course_deg(expected_float);
  Serial.print(s.get_gps_ground_course_deg() == expected_float ? PASS : FAIL);
  Serial.print("gps_ground_course_deg = ");
  Serial.println(s.get_gps_ground_course_deg());

  s.set_gps_ground_speed_kt(expected_float);
  Serial.print(s.get_gps_ground_speed_kt() == expected_float ? PASS : FAIL);
  Serial.print("gps_ground_speed_kt = ");
  Serial.println(s.get_gps_ground_speed_kt());

  s.set_gps_satcount(expected_uint8_t);
  Serial.print(s.get_gps_satcount() == expected_uint8_t ? PASS : FAIL);
  Serial.print("gps_satcount = ");
  Serial.println(s.get_gps_satcount());

  s.set_heading_raw(expected_uint16_t);
  Serial.print(s.get_heading_raw() == expected_uint16_t ? PASS : FAIL);
  Serial.print("heading_raw = ");
  Serial.println(s.get_heading_raw());

  s.set_heading_deg(expected_float);
  Serial.print(s.get_heading_deg() == expected_float ? PASS : FAIL);
  Serial.print("heading_deg = ");
  Serial.println(s.get_heading_deg());

  s.set_pitch_deg(expected_int8_t);
  Serial.print(s.get_pitch_deg() == expected_int8_t ? PASS : FAIL);
  Serial.print("pitch_deg = ");
  Serial.println(s.get_pitch_deg());

  s.set_roll_deg(expected_int8_t);
  Serial.print(s.get_roll_deg() == expected_int8_t ? PASS : FAIL);
  Serial.print("roll_deg = ");
  Serial.println(s.get_roll_deg());

  s.set_odometer_ticks(expected_uint32_t);
  Serial.print(s.get_odometer_ticks() == expected_uint32_t ? PASS : FAIL);
  Serial.print("odometer_ticks = ");
  Serial.println(s.get_odometer_ticks());

  s.set_odometer_timestamp(expected_uint16_t);
  Serial.print(s.get_odometer_timestamp() == expected_uint16_t ? PASS : FAIL);
  Serial.print("odometer_timestamp = ");
  Serial.println(s.get_odometer_timestamp(), DEC);

  s.set_odometer_ticks_are_fwd(expected_uint8_t);
  Serial.print(s.get_odometer_ticks_are_fwd() == expected_uint8_t ? PASS : FAIL);
  Serial.print("odometer_ticks_are_fwd = ");
  Serial.println(s.get_odometer_ticks_are_fwd());

  s.set_nav_heading_deg(expected_float);
  Serial.print(s.get_nav_heading_deg() == expected_float ? PASS : FAIL);
  Serial.print("nav_heading_deg = ");
  Serial.println(s.get_nav_heading_deg());

  s.set_nav_gps_heading(expected_float);
  Serial.print(s.get_nav_gps_heading() == expected_float ? PASS : FAIL);
  Serial.print("nav_gps_heading = ");
  Serial.println(s.get_nav_gps_heading());

  s.set_nav_latitude(expected_float);
  Serial.print(s.get_nav_latitude() == expected_float ? PASS : FAIL);
  Serial.print("nav_latitude = ");
  Serial.println(s.get_nav_latitude());

  s.set_nav_longitude(expected_float);
  Serial.print(s.get_nav_longitude() == expected_float ? PASS : FAIL);
  Serial.print("nav_longitude = ");
  Serial.println(s.get_nav_longitude());

  s.set_nav_waypt_latitude(expected_float);
  Serial.print(s.get_nav_waypt_latitude() == expected_float ? PASS : FAIL);
  Serial.print("nav_waypt_latitude = ");
  Serial.println(s.get_nav_waypt_latitude());

  s.set_nav_waypt_longitude(expected_float);
  Serial.print(s.get_nav_waypt_longitude() == expected_float ? PASS : FAIL);
  Serial.print("nav_waypt_longitude = ");
  Serial.println(s.get_nav_waypt_longitude());

  s.set_nav_rel_bearing_deg(expected_float);
  Serial.print(s.get_nav_rel_bearing_deg() == expected_float ? PASS : FAIL);
  Serial.print("nav_rel_bearing_deg = ");
  Serial.println(s.get_nav_rel_bearing_deg());

  s.set_nav_distance_to_waypt_m(expected_float);
  Serial.print(s.get_nav_distance_to_waypt_m() == expected_float ? PASS : FAIL);
  Serial.print("nav_distance_to_waypt_m = ");
  Serial.println(s.get_nav_distance_to_waypt_m());

  s.set_nav_speed(expected_float);
  Serial.print(s.get_nav_speed() == expected_float ? PASS : FAIL);
  Serial.print("nav_speed = ");
  Serial.println(s.get_nav_speed());

  s.set_mobility_motor_pwm(expected_uint16_t);
  Serial.print(s.get_mobility_motor_pwm() == expected_uint16_t ? PASS : FAIL);
  Serial.print("mobility_motor_pwm = ");
  Serial.println(s.get_mobility_motor_pwm());

  s.set_mobility_steering_pwm(expected_uint16_t);
  Serial.print(s.get_mobility_steering_pwm() == expected_uint16_t ? PASS : FAIL);
  Serial.print("mobility_steering_pwm = ");
  Serial.println(s.get_mobility_steering_pwm());

  s.set_control_heading_desired(expected_float);
  Serial.print(s.get_control_heading_desired() == expected_float ? PASS : FAIL);
  Serial.print("control_heading_desired = ");
  Serial.println(s.get_control_heading_desired());

  s.set_control_xtrack_error(expected_float);
  Serial.print(s.get_control_xtrack_error() == expected_float ? PASS : FAIL);
  Serial.print("control_xtrack_error = ");
  Serial.println(s.get_control_xtrack_error());

  s.set_control_xtrack_error_rate(expected_float);
  Serial.print(s.get_control_xtrack_error_rate() == expected_float ? PASS : FAIL);
  Serial.print("control_xtrack_error_rate = ");
  Serial.println(s.get_control_xtrack_error_rate());

  s.set_control_xtrack_error_sum(expected_float);
  Serial.print(s.get_control_xtrack_error_sum() == expected_float ? PASS : FAIL);
  Serial.print("control_xtrack_error_sum = ");
  Serial.println(s.get_control_xtrack_error_sum());

  s.set_control_steering_pwm(expected_float);
  Serial.print(s.get_control_steering_pwm() == expected_float ? PASS : FAIL);
  Serial.print("control_steering_pwm = ");
  Serial.println(s.get_control_steering_pwm());

  s.set_suffix(expected_uint32_t);
  Serial.print(s.get_suffix() == expected_uint32_t ? PASS : FAIL);
  Serial.print("suffix = ");
  Serial.println(s.get_suffix(), HEX);

  Serial.println("---- end of test ----");

}
