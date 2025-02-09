#include "src-arduino/HCSR04.h"
#include "/tests/lightbyte.h"

// set the pin numbers to be used by each module
void setup() { 
  lightbyte_config({31, 33, 35, 37, 39, 41, 43, 45});
  ultrasonic_config(50, 46);
  }
}

void loop() {
  intbyte(0);
  floatbyte(measure(), 5);
  delay(500);
}
