// Device pinout - GPIO assignment
byte cs;
byte clk;
byte din;

// make shift-out slower
int wait = 0;

//byte pinout[] = {31, 33, 35, 37, 39, 41, 43, 45};
bool eightbits[] = {0, 0, 0, 0, 0, 0, 0, 0};
void int_to_bin(byte value) {
  for (int i = 7; i != -1; i--) {
    int place = 1 << i;
    if (value >= place) {
      value -= place;
      eightbits[7-i] = 1;
    }
    else {
        eightbits[7-i] = 0;
    }
  }
  //for (byte i = 0; i != 8; i++) {
    //digitalWrite(pinout[i], eightbits[i]);}
}

// assign gpio pin numbers
void led_assign_pins(byte chipselect, byte clockpin, byte data) {
  cs = chipselect;
  clk = clockpin;
  din = data;
  pinMode(cs, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(din, OUTPUT);
}

// shift out 16 bits
// address is the register address in the IC; cannot exceed value of 15
// data is a string or array with 8 binary digits
// can also be an int array, or a str array
// if positive is 0, all data bits will be inverted
void shout(byte addr, bool data[], bool positive = true) {
  int_to_bin(addr);
  for (byte i; i != 8; i++) {
    if (eightbits[i]) {
      digitalWrite(din, 1);
    }
    else {
      digitalWrite(din, 0);
    }
    digitalWrite(clk, 1);
    delay(wait);
    digitalWrite(clk, 0);
  }
  for (byte i = 0; i != 8; i++) {
    if (data[i] == positive) {
      digitalWrite(din, 1);
    }
    else {
      digitalWrite(din, 0);
    }
    digitalWrite(clk, 1);
    delay(wait);
    digitalWrite(clk, 0);
  }
  digitalWrite(cs, 1);
  delay(wait);
  digitalWrite(cs, 0);
  digitalWrite(clk, 0);
  digitalWrite(din, 0);
}

// display an image (8x8 2D array)
void image_out(bool image[8][8], bool mode = true) {
  //for (byte i = 1; i != 9; i++) {
    //shout(i, image[i-1], mode);
  //}
  shout(1, image[0], mode);
  shout(2, image[1], mode);
  shout(3, image[2], mode);
  shout(4, image[3], mode);
  shout(5, image[4], mode);
  shout(6, image[5], mode);
  shout(7, image[6], mode);
  shout(8, image[7], mode);
}

// initialize/configure the display (clears the display)
// intensity is display brightness, 0 is lowest
// scanlimit is the highest data register scanned
// shutdown_mode = True to enter the IC's shutdown mode
// display_test = True to enter the IC's display test mode
// timedelay sets a delay time for shift-out, make it non-zero if you want to slow down output
void led_config(byte intensity = 0, 
                byte scanlimit = 7,
                bool shutdown_mode = false,
                bool display_test = false,
                int timedelay = 0) {
  wait = timedelay;
  bool line[] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int reg = 0; reg != 16; reg++) {
    shout(reg, line, 1);
  }
  
  int_to_bin(shutdown_mode);
  memcpy(line, eightbits, 8);
  shout(12, line, 0);
  
  int_to_bin(intensity);
  memcpy(line, eightbits, 8);
  shout(10, line, 1);
  
  int_to_bin(scanlimit);
  memcpy(line, eightbits, 8);
  shout(11, line, 1);
  
  int_to_bin(display_test);
  memcpy(line, eightbits, 8);
  shout(15, line, 1);

  //bool myarr[] = {1, 0, 0, 1, 1, 0, 0, 1};
  //shout(8, myarr, 1);
}

// rotate an image 90 degrees ccw
// a is the image
// halfpi is the number of times to rotate 
void rotate(bool a[8][8], int halfpi) {
  for (byte turn = 0; turn != halfpi%4; turn++) {
    bool b[8][8];
    for (byte y = 0; y != 8; y++) {
      for (byte x = 0; x != 8; x++) {
        b[7-x][y] = a[y][x];
      }
    }
    memcpy(a, b, 64);
  }
}