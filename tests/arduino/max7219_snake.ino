#include "/Users/adaaspirations/Documents/Arduino/libraries/max7219.h"
#include "/Users/adaaspirations/Documents/Arduino/libraries/joystick.h"

// every body segment of the snake is a single SnakeSegment
struct SnakeSegment {
  byte x;
  byte y;
  byte heading;
  SnakeSegment* next_segment;
};


bool loss[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0, 1, 0, 0},
                   {0, 0, 1, 0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 1, 1, 0, 0, 0},
                   {0, 0, 1, 0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},};

// map of points where the snake changes heading
char pivot_points[8][8];

// the 8x8 grid displayed
bool board[8][8];

// the snake
SnakeSegment snake;

// the apple
byte apple[2];

// allows the framerate to be decreased while maintaining high input scan rate
byte counter = 0;

// new input will not be read until this is cleared
bool input_flag = 0;

// append a new segment to the tail of the snake
void newSegment(SnakeSegment* head) {
  // find the current tail of the snake
  SnakeSegment* current = head;
  while (current->next_segment) {
    current = current->next_segment;
  }

  // create the new tail
  current->next_segment = malloc(sizeof(SnakeSegment));
  SnakeSegment* new_tail = current->next_segment;
  
  // assign the new tail's potition based on the heading of the previous segment
  if (current->heading % 2) {
    new_tail->y = current->y - (2 - current->heading);
    new_tail->x = current->x;
  }
  else {
    new_tail->x = current->x + (3 - current->heading);
    new_tail->y = current->y;
  }
   
  new_tail->heading = current->heading;
  new_tail->next_segment = 0;

  return;
}


// returns true if the input coordinates overlap with any part of the snake except the head
bool checkCollision(byte input_x, byte input_y) {
  bool collision = 0;

  SnakeSegment* tocheck = snake.next_segment;
  do {
    collision = input_x == tocheck->x && input_y == tocheck->y;
    tocheck = tocheck->next_segment;
  } while (tocheck->next_segment && !collision);
  
  return collision;
}


// generate an apple at a random location on the board
void generateApple() {
  do {
    apple[0] = (byte)random(8);
    apple[1] = (byte)random(8);
  } while (false);
//while (checkCollision(apple[0], apple[1]));
  return;
}


void setup() {
  joystick_assign_pins(8, 7, 3);
  led_assign_pins(15, 16, 14);
  led_config(0, 7, 0, 0, 0);

  randomSeed(analogRead(0));
  memset(&pivot_points, 0, 64);
  //pivot_points[2][4] = 4;
  
  snake.x = 0;
  snake.y = 0;
  snake.heading = 1;
  snake.next_segment = 0;
  newSegment(&snake);
  newSegment(&snake);
  //Serial.begin(9600);
  generateApple();
}


void loop() {
  // only perform game logic on some iterations
  if (!counter) {
    input_flag = 0;
    memset(&board, 0, 64);
    
    // detect game over
    if (snake.x > 7 || snake.y > 7 || checkCollision(snake.x, snake.y)) {
      memcpy(board, loss, 64);
      rotate(board, 3);
      image_out(board);
      while (true) {}
    }

    // eat apples
    if (checkCollision(apple[0], apple[1])) {
      newSegment(&snake);
      generateApple();
    }
    else {
      board[apple[1]][apple[0]] = 1;
    }
    
    // add a new pivot point based on player input
    if (stick_position[0] == -1 and snake.heading != 3) {
      //Serial.println("Turning up");
      pivot_points[snake.y][snake.x] = 1;
    }
    else if (stick_position[0] == 1 and snake.heading != 1) {
      pivot_points[snake.y][snake.x] = 3;
      //Serial.println("Turning down");
    }
    else if (stick_position[1] == -1 and snake.heading != 4) {
      pivot_points[snake.y][snake.x] = 2;
      //Serial.println("Turning right");
    }
    else if (stick_position[1] == 1 and snake.heading != 4) {
      pivot_points[snake.y][snake.x] = 4;
      //Serial.println("Turning left");
    }

    // move each body segment of the snake
    SnakeSegment* seg = &snake;
    while (seg) {
      //Serial.print(seg->x);
      //Serial.print(", ");
      //Serial.println(seg->y);
      // handle direction changes
      if (pivot_points[seg->y][seg->x]) {
        seg->heading = pivot_points[seg->y][seg->x];
      }

      // remove pivot points after the snake has passed them
      int view = (int)seg->next_segment;
      //Serial.println(view);
      if (!view) {
        pivot_points[seg->y][seg->x] = 0; 
      }
      
      // move and display body segments
      if (seg->heading % 2) {
        seg->y += (2 - seg->heading); 
      }
      else {
        seg->x -= (3 - seg->heading);
      }
      
      // add snake body to the board
      if (seg->x < 8 and seg->y < 8){
        board[seg->y][seg->x] = 1;
      }
      
      seg = seg->next_segment;
    }
    //Serial.print("\n");
    rotate(board, 1);
    image_out(board);
  }
  
  // get joystick input for next frame
  if (!input_flag) {
    readJoystick();
    formatInput(20, 1);
  }
  
  if (stick_position[0] or stick_position[1]) {
    input_flag = 1;
  }
  
  counter++;
  delay(2);
}
