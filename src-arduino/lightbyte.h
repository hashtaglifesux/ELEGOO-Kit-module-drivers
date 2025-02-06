// display an integer value in binary using LEDs
// pins used for each LED, MSB first
byte pinout[] = {31, 33, 35, 37, 39, 41, 43, 45};

void binary(byte value) {
  bool eightbits[] = {0, 0, 0, 0, 0 ,0 ,0, 0};
  for (byte i = 7; i != -1; i--) {
    byte place = 1 << i;
    if (value >= place) {
      value -= place;
      eightbits[7-i] = 1;
    }
    else {
        eightbits[7-i] = 0;
    }
    for (byte j = 0; j != 8; j++) {
        digitalWrite(pinout[j], eightbits[j]);
    }
  }
}
