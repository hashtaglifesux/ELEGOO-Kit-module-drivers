#include "/Users/adaaspirations/Documents/Arduino/libraries/lightbyte.h"
byte clk = 50;
byte dt = 48;
byte sw = 46;

byte number = 0;

void setup() {
  for (int j = 0; j != 8; j++) {
    digitalWrite(pinout[j], OUTPUT);
  }
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT);
}

void loop() {
  int flag = false;
  while (not digitalRead(dt)) {
    flag = false;
    while (not digitalRead(clk)) {
      if (digitalRead(dt)) {
        flag = true;
        break;
      }
    }
    if (flag) {
      number += 1;
      break;
    }
  }
  while (not digitalRead(clk)) {
    flag = false;
    while (not digitalRead(dt)) {
      if (digitalRead(clk)) {
        flag = true;
        break;
      }
    }
    if (flag) {
      number -= 1;
      break;
    }
  }
  binary(number);
}
