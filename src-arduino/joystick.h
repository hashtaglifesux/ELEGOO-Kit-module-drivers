byte vrx;
byte vry;
byte sw;
short stick_input[2];
short stick_position[2];

void joystick_assign_pins(byte VRx, byte VRy, byte SW) {
  vrx = VRx;
  vry = VRy;
  
  pinMode(SW, INPUT);
  sw = SW;
}


// read the x and y values (0-1023) and store them in stick_input
// return the value of the push button
bool readJoystick() {
  stick_input[0] = analogRead(vrx);
  stick_input[1] = analogRead(vry);
  
  return digitalRead(sw);
}


// convert the raw x-y input data into a signed vector, stored in stick_position
// threshold (0-511) is the minimum amount the joystick must be moved to have effect
// scale scales the values to be represented by the specified number of bits
short* formatInput(short threshold, byte scale) {
  byte shr = 10 - scale;
  stick_position[0] = stick_input[0] - 511;
  stick_position[1] = stick_input[1] - 511;
  
  if (abs(stick_position[0]) < threshold) {
    stick_position[0] = 0;
  }
  if (abs(stick_position[1]) < threshold) {
    stick_position[1] = 0;
  }
  
  stick_position[0] = stick_position[0] >> shr;
  stick_position[1] = stick_position[1] >> shr;
  
  return stick_position;
}
