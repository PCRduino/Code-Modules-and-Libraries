//RGBModule.ino

// copy these into the globals section of your main sketch
//const byte redPin = 0;  //Define pin for Blue LED
//const byte greenPin = 1;  //Define pin for Green LED
//const byte bluePin = 2;  //Define pin for Red LED

void LEDSetup() {
  // set pin modes for RGB LEDs
  pinMode(redPin, OUTPUT);  //Set pin to Output
  pinMode(greenPin, OUTPUT);  //Set pin to Output
  pinMode(bluePin, OUTPUT);  //Set pin to Output
}


// Simple Flashes
//*********************************************
void flashRed() {
  digitalWrite(redPin, HIGH); //Turn on LED
  delay(500); // Delay for 0.5 second
  digitalWrite(redPin, LOW); //Turn off LED
}
void flashGreen() {
  digitalWrite(greenPin, HIGH); //Turn on LED
  delay(500); // Delay for 0.5 second
  digitalWrite(greenPin, LOW); //Turn off LED
}
void flashBlue() {
  digitalWrite(bluePin, HIGH); //Turn on LED
  delay(500); // Delay for 0.5 second
  digitalWrite(bluePin, LOW); //Turn off LED
}


// Simple flashes with arguments
//*********************************************
void flashRedDelay(int onTime) {
  digitalWrite(redPin, HIGH); //Turn on LED
  delay(onTime); // Delay for the time in the argument
  digitalWrite(redPin, LOW); //Turn off LED
}
void flashGreenDelay(int onTime) {
  digitalWrite(greenPin, HIGH); //Turn on LED
  delay(onTime); // Delay for the time in the argument
  digitalWrite(greenPin, LOW); //Turn off LED
}
void flashBlueDelay(int onTime) {
  digitalWrite(bluePin, HIGH); //Turn on LED
  delay(onTime); // Delay for the time in the argument
  digitalWrite(bluePin, LOW); //Turn off LED
}


// Flashes with user-defined LED pin number and delay time
//*********************************************
void flashPin(byte pinNum, int onTime) {
  digitalWrite(pinNum, HIGH); //Turn on LED
  delay(onTime); // Delay for the time in the argument
  digitalWrite(pinNum, LOW); //Turn off LED
}


// Flashes that respond to user-defined red, gree, and blue pin states and delay time
//*********************************************
void flashRGB(byte r, byte g, byte b, int onTime) {
  digitalWrite(redPin, r); //Turn on LED if r = 1
  digitalWrite(greenPin, g); //Turn on LED if g = 1
  digitalWrite(bluePin, b); //Turn on LED if b = 1
  delay(onTime); // Delay for the time in the argument
  digitalWrite(redPin, LOW); //Turn off LED
  digitalWrite(greenPin, LOW); //Turn off LED
  digitalWrite(bluePin, LOW); //Turn off LED
}

// Sends test flashes to an RGB LED: 1 red, 2 green, 3 blue
//*********************************************
void testFlashRBGled() {
  while (true) {
    // flash red once:
    flashRGB(1, 0, 0, 250);
    delay(500);

    // flash green twice
    for (int i = 0; i < 2; i++) {
      flashRGB(0, 1, 0, 250);
      delay(500);
    }

    // flash blue thrice
    for (int i = 0; i < 3; i++) {
      flashRGB(0, 0, 1, 250);
      delay(500);
    }
  }
}

