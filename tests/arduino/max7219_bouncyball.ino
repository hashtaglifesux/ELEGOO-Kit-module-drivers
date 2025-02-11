#include "/Users/adaaspirations/Documents/Arduino/max7219/max7219.h"

bool arr[8][8] = {{1, 1, 1, 1, 1, 1, 1, 1},
                  {1, 0, 0, 0, 0, 0, 0, 1},
                  {1, 0, 1, 1, 1, 1, 0, 1},
                  {1, 0, 1, 0, 0, 1, 0, 1},
                  {1, 0, 1, 0, 0, 1, 0, 1},
                  {1, 0, 1, 1, 1, 1, 0, 1},
                  {1, 0, 0, 0, 0, 0, 0, 1},
                  {1, 1, 1, 1, 1, 1, 1, 1}};

bool board[8][8];
byte ball[] = {4, 0, 2, 1};

void setup() {
  led_assign_pins(23, 46, 50);
  led_config(0, 7, 0, 0, 0.2);
  image_out(arr);
  delay(1000);
}

void loop() {
  delay(250);
  memset(&board, 0, 64);
  ball[0] += ball[2];
  ball[1] += ball[3];
  
  board[ball[0]][ball[1]] = 1;
  
  if (ball[0] == 0 or ball[0] == 7) {
    ball[2] = 0-ball[2];
  }
  if (ball[1] == 0 or ball[1] == 7) {
    ball[3] = 0-ball[3];
  }
  image_out(board);
}
