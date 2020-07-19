/* LEDModule.ino by c.d.odom 2017
  // put these lines at the TOP of your MAIN sketch!
  int onboardLEDPin = 13;
  int redPin = A9;
  int greenPin = A8;
  int bluePin = A7;

  void setup() {
    pinMode(onboardLEDPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  }
*/


void blinkOK() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(onboardLEDPin, HIGH);
    delay(500);
    digitalWrite(onboardLEDPin, LOW);
    delay(500);
  }
}

void blinkNum(int numBlinks) {
  for (int i = 0; i < numBlinks; i++) {
    digitalWrite(onboardLEDPin, HIGH);
    delay(500);
    digitalWrite(onboardLEDPin, LOW);
    delay(500);
  }
}

void blinkLEDNum(int LEDPin, int numBlinks) {
  for (int i = 0; i < numBlinks; i++) {
    digitalWrite(LEDPin, HIGH);
    delay(200);
    digitalWrite(LEDPin, LOW);
    delay(100);
  }
}

void digitalRGB(int rState, int gState, int bState) {
  digitalWrite(redPin, rState);   // control the red LED
  digitalWrite(greenPin, gState); // control the green LED
  digitalWrite(bluePin, bState);  // control the blue LED
}

void fadeInLED(int LEDPin) {
  // LED must be plugged into PWM pin!
  for (int i = 0; i <= 255; i++) {
    analogWrite(LEDPin, i);         // cause the LED to glow between full off and full on
    delay(5);                 // glow so human eye can register the LED glow
  }
}

void fadeOutLED(int LEDPin) {
  // LED must be plugged into PWM pin!
  for (int i = 255; i >= 0; i--) {
    analogWrite(LEDPin, i);         // cause the LED to glow between full off and full on
    delay(5);                 // glow so human eye can register the LED glow
  }
}

void displayRGB(int r, int g, int b, int gT) {
  analogWrite(redPin, r); // excite the red LED
  analogWrite(greenPin, g); // excite the green LED
  analogWrite(bluePin, b);  // excite the blue LED
  delay(gT);  // delay long so eye can register
}

