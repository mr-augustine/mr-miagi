#ifndef _PINS_H_
#define _PINS_H_

#include <avr/io.h>

////////////////////////////////////////////////////////////////////////////////
// MOBILITY
#define MOBILITY_TOP          OCR3A
#define STEERING_COMPARE_REG  OCR3B
#define THROTTLE_COMPARE_REG  OCR3C

#define MOBILITY_TCCRA      TCCR3A
#define MOBILITY_TCCRB      TCCR3B
#define MOBILITY_TIMER      TCNT3

#define STEERING_PORT       PORTE
#define STEERING_DDR        DDRE
#define STEERING_PINVEC     PINE
#define STEERING_DDR_PIN    DDE4    // Mega Digital Pin 2
#define STEERING_COMP_MODE  (1 << COM3B1)

#define THROTTLE_PORT       PORTE
#define THROTTLE_DDR        DDRE
#define THROTTLE_PINVEC     PINE
#define THROTTLE_DDR_PIN    DDE5    // Mega Digital Pin 3
#define THROTTLE_COMP_MODE  (1 << COM3C1)

#endif
