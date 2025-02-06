// device pinout - GPIO assignment
byte trig;
byte echo;

// returns the distance in meters
// mach = speed of sound in m/s
float measure(int mach = 343) {
  digitalWrite(trig, HIGH);
  delay(0.01); // minimum is 0.01
  digitalWrite(trig, LOW);
  while (not digitalRead(echo)) {
  }
  unsigned long StartTime = millis();
  while (digitalRead(echo)) {
  }
  unsigned long EndTime = millis();
  return (EndTime-StartTime)*mach/2;
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, OUTPUT);
}

void loop() {}
