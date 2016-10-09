#include "mobility.h"

void setup() {
  noInterrupts();

  // Although not needed, init_mobility() helped me figure out what the
  // issue was with my mobility_init() function.
  //init_mobility();
  
  mobility_init();
  interrupts();
}

void loop() {

}
