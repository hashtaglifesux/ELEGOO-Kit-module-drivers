// stores the pin assignments, raw input, and processed input of a joystick
struct Joystick {
  byte vrx;
  byte vry;
  byte sw;
  short stick_input[2];
  short stick_position[2];
};


// initialize a joystick and assign pins vrx, vry, and sw
Joystick *joystick_assign_pins(byte VRx, byte VRy, byte SW) {
  Joystick *newJoystick = malloc(sizeof(Joystick));
  newJoystick->vrx = VRx;
  newJoystick->vry = VRy;
  newJoystick->sw = SW;
  
  pinMode(SW, INPUT);

  return newJoystick;
}


// read the x and y values (0-1023) and store them in stick_input
// return the value of the push button
bool readJoystick(Joystick *j_to_read) {
  j_to_read->stick_input[0] = analogRead(vrx);
  j_to_read->stick_input[1] = analogRead(vry);
  
  return digitalRead(j_to_read->sw);
}


// convert the raw x-y input data into a signed vector, stored in stick_position
// threshold (0-511) is the minimum amount the joystick must be moved to have effect
// scale scales the values to be represented by the specified number of bits
short* formatInput(short threshold, byte scale, Joystick *j_to_format) {
  byte shr = 10 - scale;
  j_to_format->stick_position[0] = j_to_format->stick_input[0] - 511;
  j_to_format->stick_position[1] = j_to_format->stick_input[1] - 511;
  
  if (abs(j_to_format->stick_position[0]) < threshold) {
    j_to_format->stick_position[0] = 0;
  }
  if (abs(j_to_format->stick_position[1]) < threshold) {
    j_to_format->stick_position[1] = 0;
  }
  
  j_to_format->stick_position[0] = j_to_format->stick_position[0] >> shr;
  j_to_format->stick_position[1] = j_to_format->stick_position[1] >> shr;
  
  return j_to_format->stick_position;
}
