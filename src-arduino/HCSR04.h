// device pinout - GPIO assignment
byte trig;
byte echo;

// assign what gpio pins you will be using
void ultrasonic_assign_pins(byte trig_pin, byte echo_pin) {
  trig = trig_pin;
  echo = echo_pin;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

// returns the distance in meters
// mach = speed of sound in m/s
float measure(int mach = 343) {
  int sum = 0;
  for (byte i = 0; i < 10; i++) {
    digitalWrite(trig, HIGH);
    delay(0.01); // minimum is 0.01
    digitalWrite(trig, LOW);
    while (not digitalRead(echo)) {
    }
    int StartTime = millis();
    while (digitalRead(echo)) {
    }
    int EndTime = millis();
    sum += (EndTime-StartTime);
    delay(4.5);
  }
  return (float)sum*(float)mach/20000.0;
}
