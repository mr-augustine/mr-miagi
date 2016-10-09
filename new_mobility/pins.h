#ifndef _PINS_H_
#define _PINS_H_

#include <avr/io.h>

////////////////////////////////////////////////////////////////////////////////
// MOBILITY
#define STEERING_PORT       PORTE
#define STEERING_DDR        DDRE
#define STEERING_PINVEC     PINE
#define STEERING_PIN        DDE4
//#define STEERING_PIN        PE4     // Mega Digital Pin 2

#define THROTTLE_PORT       PORTE
#define THROTTLE_DDR        DDRE
#define THROTTLE_PINVEC     PINE
//#define THROTTLE_PIN        DDE5
#define THROTTLE_PIN        PE5     // Mega Digital Pin 3

#endif
