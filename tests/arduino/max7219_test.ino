#include "/Users/adaaspirations/Documents/Arduino/max7219/max7219.h"

bool amogus[8][8] = {{0, 0, 1, 1, 1, 1, 0, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {1, 1, 1, 1, 0, 0, 0, 1},
                     {1, 1, 1, 1, 0, 0, 0, 1},
                     {1, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 0, 0, 1, 1, 0},
                     {0, 1, 1, 0, 0, 1, 1, 0}};

void setup() {
  led_assign_pins(23, 46, 50);
  led_config(100, 7, 0, 0, 0.2);
}

void loop() {
  for (int k = 3; k != 256; k++) {
    rotate(amogus, k);
    image_out(amogus);
    delay(1000);
  }
}
