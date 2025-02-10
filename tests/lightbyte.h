// use 8 LEDs to display an integer or floating-point value in binary

int pinout[8];

// configure the pins used for each LED, MSB first
void lightbyte_init(int pins[8]) {
  for (int i = 0; i!=8; i++) {
    pinout[i] = pins[i];
    pinMode(pinout[i], OUTPUT);
  }
}

// convert an integer to binary
void intbyte(byte val) {
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

// convert a float to binary- 'precision' specifies how many bits will 
// be reserved for the non-integer part
void floatbyte(float value, byte precision) {
    byte val =  (byte)(value * (2 << precision-1));
    bool eightbits[] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 7; i != -1; i--) {
        byte place = 1 << i;
        if (val >= place) {
            val -= place;
            eightbits[7-i] = 1;
        }
        else {
            eightbits[7-i] = 0;
        }
    }
    // integer part
    for (int j = 0; j != 8-precision; j++) {
        digitalWrite(pinout[j], eightbits[j]);
    }
    // non-integer part
    for (int j = 8-precision; j != 8; j++) {
        digitalWrite(pinout[j], eightbits[j]);
    }
}
