// pins used for each LED, MSB first
int pinout[] = {31, 33, 35, 37, 39, 41, 43, 45};

void binary(byte val) {
  bool eightbits[] = {0, 0, 0, 0, 0 ,0 ,0, 0};
  for (int i = 7; i != -1; i--) {
    int place = 1 << i;
    if (val >= place) {
      val -= place;
      eightbits[7-i] = 1;
    }
    else {
        eightbits[7-i] = 0;
    }
    for (int j = 0; j != 8; j++) {
        digitalWrite(pinout[j], eightbits[j]);
    }
  }
}