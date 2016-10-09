#include "Mobility.h"

Mobility mobility;

void setup() {
  Serial.begin(9600);

  noInterrupts();

  mobility.initialize();

  int return_value = mobility.verify_init();
  if (return_value == 1) {
    Serial.println("[*] Mobility is ready");
  } else {
    Serial.println("[!] Mobility did not initialize correctly");
    Serial.print("return_value: ");
    Serial.println(return_value);
  }

  interrupts();
}

void loop() {

}
