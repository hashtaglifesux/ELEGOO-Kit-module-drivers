#include "/Users/adaaspirations/Documents/Arduino/libraries/lightbyte.h"
// device pinout - GPIO assignment
byte trig = 50;
byte echo = 46;

// returns the distance in meters
// mach = speed of sound in m/s
float measure(int mach = 343) {
  digitalWrite(trig, HIGH);
  delay(0.1); // minimum is 0.01
  digitalWrite(trig, LOW);
  while (not digitalRead(echo)) {
  }
  float StartTime = (float)millis();
  while (digitalRead(echo)) {
  }
  float EndTime = (float)millis();
  return (EndTime-StartTime)* (float)mach/2000.0;
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  for (int j = 0; j != 8; j++) {
    pinMode(pinout[j], OUTPUT);
  }
}

void loop() {
  floatbyte(measure(), 5);
  delay(500);
  intbyte(0);
}
