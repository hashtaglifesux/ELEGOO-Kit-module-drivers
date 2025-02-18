// https://www.alldatasheet.com/datasheet-pdf/pdf/1574132/CRYSTAIFONTZ/LCD-1602A.html
byte pinout[] = {31, 33, 35, 37, 39, 41, 43, 45};
byte rs = 50;
byte e = 48;

bool entry_mode_set[] = {0 ,0 ,0 ,0 ,0, 1, 0, 0};
bool display_cursor_blink[] = {0, 0, 0, 0, 1, 1, 0, 0};
bool cursor_display_shift[] = {0, 0, 0, 1, 0, 0, 0, 0};
bool function_set[] = {0 ,0 ,1 ,1, 0, 0, 0, 0};

char character_dict[] = " !#$%&'()*+,-./0123456789:;<>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}";

bool character_codes[][8] {{0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 1},
                           {0, 0, 1, 0, 0, 0, 1, 1},
                           {0, 0, 1, 0, 0, 1, 0, 0},
                           {0, 0, 1, 0, 0, 1, 0, 1},
                           {0, 0, 1, 0, 0, 1, 1, 0},
                           {0, 0, 1, 0, 0, 1, 1, 1},
                           {0, 0, 1, 0, 1, 0, 0, 0},
                           {0, 0, 1, 0, 1, 0, 0, 1},
                           {0, 0, 1, 0, 1, 0, 1, 0},
                           {0, 0, 1, 0, 1, 0, 1, 1},
                           {0, 0, 1, 0, 1, 1, 0, 0},
                           {0, 0, 1, 0, 1, 1, 0, 1},
                           {0, 0, 1, 0, 1, 1, 1, 0},
                           {0, 0, 1, 0, 1, 1, 1, 1},
                           {0, 0, 1, 1, 0, 0, 0, 0},
                           {0, 0, 1, 1, 0, 0, 0, 1},
                           {0, 0, 1, 1, 0, 0, 1, 0},
                           {0, 0, 1, 1, 0, 0, 1, 1},
                           {0, 0, 1, 1, 0, 1, 0, 0},
                           {0, 0, 1, 1, 0, 1, 0, 1},
                           {0, 0, 1, 1, 0, 1, 1, 0},
                           {0, 0, 1, 1, 0, 1, 1, 1},
                           {0, 0, 1, 1, 1, 0, 0, 0},
                           {0, 0, 1, 1, 1, 0, 0, 1},
                           {0, 0, 1, 1, 1, 0, 1, 0},
                           {0, 0, 1, 1, 1, 0, 1, 1},
                           {0, 0, 1, 1, 1, 1, 0, 0},
                           {0, 0, 1, 1, 1, 1, 1, 0},
                           {0, 0, 1, 1, 1, 1, 1, 1},
                           {0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 0, 0, 1},
                           {0, 1, 0, 0, 0, 0, 1, 0},
                           {0, 1, 0, 0, 0, 0, 1, 1},
                           {0, 1, 0, 0, 0, 1, 0, 0},
                           {0, 1, 0, 0, 0, 1, 0, 1},
                           {0, 1, 0, 0, 0, 1, 1, 0},
                           {0, 1, 0, 0, 0, 1, 1, 1},
                           {0, 1, 0, 0, 1, 0, 0, 0},
                           {0, 1, 0, 0, 1, 0, 0, 1},
                           {0, 1, 0, 0, 1, 0, 1, 0},
                           {0, 1, 0, 0, 1, 0, 1, 1},
                           {0, 1, 0, 0, 1, 1, 0, 0},
                           {0, 1, 0, 0, 1, 1, 0, 1},
                           {0, 1, 0, 0, 1, 1, 1, 0},
                           {0, 1, 0, 0, 1, 1, 1, 1},
                           {0, 1, 0, 1, 0, 0, 0, 0},
                           {0, 1, 0, 1, 0, 0, 0, 1},
                           {0, 1, 0, 1, 0, 0, 1, 0},
                           {0, 1, 0, 1, 0, 0, 1, 1},
                           {0, 1, 0, 1, 0, 1, 0, 0},
                           {0, 1, 0, 1, 0, 1, 0, 1},
                           {0, 1, 0, 1, 0, 1, 1, 0},
                           {0, 1, 0, 1, 0, 1, 1, 1},
                           {0, 1, 0, 1, 1, 0, 0, 0},
                           {0, 1, 0, 1, 1, 0, 0, 1},
                           {0, 1, 0, 1, 1, 0, 1, 0},
                           {0, 1, 0, 1, 1, 0, 1, 1},
                           {0, 1, 0, 1, 1, 1, 0, 1},
                           {0, 1, 0, 1, 1, 1, 1, 0},
                           {0, 1, 0, 1, 1, 1, 1, 1},
                           {0, 1, 1, 0, 0, 0, 0, 0},
                           {0, 1, 1, 0, 0, 0, 0, 1},
                           {0, 1, 1, 0, 0, 0, 1, 0},
                           {0, 1, 1, 0, 0, 0, 1, 1},
                           {0, 1, 1, 0, 0, 1, 0, 0},
                           {0, 1, 1, 0, 0, 1, 0, 1},
                           {0, 1, 1, 0, 0, 1, 1, 0},
                           {0, 1, 1, 0, 0, 1, 1, 1},
                           {0, 1, 1, 0, 1, 0, 0, 0},
                           {0, 1, 1, 0, 1, 0, 0, 1},
                           {0, 1, 1, 0, 1, 0, 1, 0},
                           {0, 1, 1, 0, 1, 0, 1, 1},
                           {0, 1, 1, 0, 1, 1, 0, 0},
                           {0, 1, 1, 0, 1, 1, 0, 1},
                           {0, 1, 1, 0, 1, 1, 1, 0},
                           {0, 1, 1, 0, 1, 1, 1, 1},
                           {0, 1, 1, 1, 0, 0, 0, 0},
                           {0, 1, 1, 1, 0, 0, 0, 1},
                           {0, 1, 1, 1, 0, 0, 1, 0},
                           {0, 1, 1, 1, 0, 0, 1, 1},
                           {0, 1, 1, 1, 0, 1, 0, 0},
                           {0, 1, 1, 1, 0, 1, 0, 1},
                           {0, 1, 1, 1, 0, 1, 1, 0},
                           {0, 1, 1, 1, 0, 1, 1, 1},
                           {0, 1, 1, 1, 1, 0, 0, 1},
                           {0, 1, 1, 1, 1, 0, 1, 0},
                           {0, 1, 1, 1, 1, 0, 1, 1},
                           {0, 1, 1, 1, 1, 1, 0, 0},
                           {0, 1, 1, 1, 1, 1, 0, 1}};

void lcdOut(bool eightbits[]) {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(pinout[i], eightbits[i]);
  }
  digitalWrite(e, 1);
  delay(8);
  digitalWrite(e, 0);
}

void lcdWrite(bool data[]) {
  digitalWrite(rs, 1);
  lcdOut(data);
  digitalWrite(rs, 0);
}

// clear the display
void clearDisplay() {
  bool cd[] = {0 ,0 ,0, 0, 0, 0, 0, 1};
  lcdOut(cd);
}

// move the cursor back to the first position
void returnHome() {
  bool rh[] = {0 ,0 ,0, 0, 0, 0, 1, 0};
  lcdOut(rh);
}

// make the cursor visible
void cursorVisible(bool on) {
  display_cursor_blink[6] = on;
  lcdOut(display_cursor_blink);
}

// enable cursor blinking
void cursorBlink(bool on) {
  display_cursor_blink[7] = on;
  lcdOut(display_cursor_blink);
}

// use both lines of the display
void twoLines(bool on) {
  function_set[4] = on;
  lcdOut(function_set);
}

// use the large font size
void bigFont(bool on) {
  function_set[5] = on;
  lcdOut(function_set);
}

// output a string to the display
void lcdText(char string[]) {
  //if (sizeof(string)
  bool validString;
  byte codeIndex;
  for (int j = 0; j < 15; j++) {
    validString = false;
    for (byte k = 0; k < sizeof(character_dict)-1; k++) {
      if (character_dict[k] == string[j]) {
        validString = true;
        codeIndex = k;
      }
    }
    if (validString) {
      lcdWrite(character_codes[codeIndex]);
    }
    else {
      //clearDisplay();
      //delay(200);
      //char errMessage[] = "Err: null_char  ";
      //lcdText(errMessage);
    }
  }
}

void setup() {
  pinMode(rs, OUTPUT);
  pinMode(e, OUTPUT);
  digitalWrite(e, 0);
  digitalWrite(rs, 0);
  for (byte i = 0; i < 8; i++) {
    pinMode(pinout[i], OUTPUT);
    digitalWrite(pinout[i], 0);
  }
  
  cursorVisible(false);
  cursorBlink(false);
  twoLines(true);

  char mystring[16] = "opqrstuvwxyz";
  lcdText(mystring);
}

void loop() {
}
