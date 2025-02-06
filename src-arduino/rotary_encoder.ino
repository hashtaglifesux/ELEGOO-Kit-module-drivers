#include "ELEGOO-Kit-module-drivers/src-arduino/lightbyte.h" // used for testing

// Device pinout - GPIO assignment 
byte clk = 50;
byte dt = 48;
byte sw = 46;

byte number = 0; // used for testing

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
      // encoder is rotating clockwise
      number += 1; // used for testing
      // dosomethinguseful();
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
      // encoder is rotating counterclockwise
      number -= 1; // used for testing
      // dosomethingelseuseful();
      break;
    }
  }
  binary(number);
}
