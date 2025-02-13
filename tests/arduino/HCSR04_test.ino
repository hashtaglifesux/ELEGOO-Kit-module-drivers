#include "src-arduino/HCSR04.h"
#include "/tests/arduino/lightbyte.h"

void setup() {
  byte arr[] = {31, 33, 35, 37, 39, 41, 43, 45};
  lightbyte_assign_pins(arr);
  ultrasonic_assign_pins(50, 46);
}

void loop() {
  floatbyte(measure(), 5);
  delay(1000);
}
