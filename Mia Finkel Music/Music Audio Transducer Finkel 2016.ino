/* musicRobot.ino by Maia Finkel on 5/15/16
   Code for a robot that produces tone with an audio transducer, with several songs,
   along with RGB LED, "keyboard," IR range sensor, and servo motors.


   Copyright Maia Finkel 2016.  All Rights Reserved.
   No part of these contents may be reproduced, copied, modified or adapted,
   without the prior written consent of the author, unless when used for educational
   and non-profit purposes.
*/



//globals

int IRrangePin = A9;
int transducerPin = A8 ;
int redPin = 4;
int greenPin = 5;
int bluePin = 6;
int cbuttonPin = A3;
int dbuttonPin = A2;
int ebuttonPin = A5;
int fbuttonPin = A7;
int gbuttonPin = A0;
int abuttonPin = A1;
int bbuttonPin = A4;
int highcbuttonPin = A6;
int octavebuttonPin = 12;

//frequency (Hz) value for pitches (s = sharp, b = flat)
float c4 = 261.63;
float cs4 = 277.18;
float db4 = 277.18;
float d4 = 293.66;
float ds4 = 311.13;
float eb4 = 311.13;
float e4 = 329.63;
float f4 = 349.23;
float fs4 = 369.99;
float gb = 369.99;
float g4 = 392.00;
float gs4 = 415.30;
float ab4 = 415.30;
float a4 = 440.00;
float as4 = 466.16;
float bb4 = 466.16;
float b4 = 493.88;
float c5 = 523.25;
float cs5 = 554.37;
float db5 = 554.37;
float d5 = 587.33;
float ds5 = 622.25;
float eb5 = 622.25;
float e5 = 659.25;
float f5 = 698.46;
float fs5 = 739.99;
float gb5 = 739.99;
float g5 = 783.99;
float gs5 = 830.61;
float ab5 = 830.61;
float a5 = (2 * a4);
float as5 = (2 * as4);
float bb5 = (2 * bb4);
float b5 = (2 * b4);
float c6 = (2 * c5);
float cs6 = (2 * cs5);
float db6 = (2 * db5);
float d6 = (2 * d5);
float ds6 = (2 * ds5);
float eb6 = (2 * eb5);
float e6 = (2 * e5);
float f6 = (2 * f5);
float fs6 = (2 * fs5);
float gb6 = (2 * gb5);
float g6 = (2 * g5);
float gs6 = (2 * gs5);
float ab6 = (2 * ab5);
float a6 = (2 * a5);
float as6 = (2 * as5);
float bb6 = (2 * bb5);
float b6 = (2 * b5);
float c7 = 2093;


//note duration (s)
int bpm = 240; //beats per minute (quarter notes)
float quarterNote = (60000 / bpm);
float halfNote = (120000 / bpm);
float wholeNote = (240000 / bpm);
float eighthNote = (30000 / bpm);
float sixteenthNote = (15000 / bpm);
float dottedHalfNote = (180000 / bpm);
float dottedQuarterNote = (90000 / bpm);
float dottedEighthNote = (45000 / bpm );
float twowholeNote = (480000 / bpm);


//Servo Motors
const int leftServo = 0;
const int rightServo = 1;

const int left_forward_fast = 1850;       // CCW Fast
const int left_forward_slow = 1670;
const int left_stop = 1500;               // Center position
const int left_backward_slow = 1400;
const int left_backward_fast = 1000;      // CW Fast

const int right_forward_fast = 1000;      // CW Fast
const int right_forward_slow = 1425;
const int right_stop = 1500;              // Center position
const int right_backward_slow = 1650;
const int right_backward_fast = 2000;      // CCW Fast

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(IRrangePin, INPUT);
  pinMode(transducerPin, OUTPUT);
  pinMode(cbuttonPin, INPUT_PULLUP);
  pinMode(dbuttonPin, INPUT_PULLUP);
  pinMode(ebuttonPin, INPUT_PULLUP);
  pinMode(fbuttonPin, INPUT_PULLUP);
  pinMode(gbuttonPin, INPUT_PULLUP);
  pinMode(abuttonPin, INPUT_PULLUP);
  pinMode(bbuttonPin, INPUT_PULLUP);
  pinMode(highcbuttonPin, INPUT_PULLUP);
  pinMode(octavebuttonPin, INPUT_PULLUP);

  pinMode(leftServo, OUTPUT);
  pinMode(rightServo, OUTPUT);
  delayMicroseconds(50);


}

void loop() {
  buttons();
  //dancebuttons();
  //IRrangePinScale();
  //IRrangePinSlide();
  SUPERMARIOBROS();
  //twinkleTwinkleDbMajor();
  //dontRunIntoThings();
  //while (true);

}

void buttons() {
  boolean cbuttonState = digitalRead(cbuttonPin);
  boolean dbuttonState = digitalRead(dbuttonPin);
  boolean ebuttonState = digitalRead(ebuttonPin);
  boolean fbuttonState = digitalRead(fbuttonPin);
  boolean gbuttonState = digitalRead(gbuttonPin);
  boolean abuttonState = digitalRead(abuttonPin);
  boolean bbuttonState = digitalRead(bbuttonPin);
  boolean highcbuttonState = digitalRead(highcbuttonPin);
  boolean octavebuttonState = digitalRead(octavebuttonPin);
  int octave = octavebuttonState;


  if (cbuttonState == false) {
    playNote(c4 + (c4 * octave));
    displayRed();
  }
  if (dbuttonState == false) {
    playNote(d4 + (d4 * octave));
    displayOrange();
  }
  if (ebuttonState == false) {
    playNote(e4 + (e4 * octave));
    displayYellow();
  }
  if (fbuttonState == false) {
    playNote(f4 + (f4 * octave));
    displayGreen();

  }
  if (gbuttonState == false) {
    playNote(g4 + (g4 * octave));
    displayTeal();
  }
  if (abuttonState == false) {
    playNote(a4 + (a4 * octave));
    displayBlue();
  }
  if (bbuttonState == false) {
    playNote(b4 + (b4 * octave));
    displayPurple();
  }
  if (highcbuttonState == false) {
    playNote(c5 + (c5  * octave));
    displayPink();

  }
}


void IRrangePinScale() {

  int IRrangePinValue = analogRead(IRrangePin);

  if (IRrangePinValue <= 250) {
    playNote(cs4);
    displayRed();
  }
  else if (IRrangePinValue < 300) {
    playNote(ds4);
    displayOrange();
  }
  else if (IRrangePinValue < 350) {
    playNote(f4);
    displayYellow();
  }
  else if (IRrangePinValue < 450) {
    playNote(fs4);
    displayGreen();
  }
  else if (IRrangePinValue < 550) {
    playNote(gs4);
    displayTeal();
  }
  else if (IRrangePinValue < 650) {
    playNote(as4);
    displayBlue();
  }
  else if (IRrangePinValue < 800) {
    playNote(c5);
    displayPurple();
  }
  else {
    playNote(cs5);
    displayPink();
  }
}

void IRrangePinSlide() {
  int sensorValue = analogRead(A9);
  float note = 2 * sensorValue;
  playNote(note);
}

void printSensor(int sPin) {
  int sensorValue;  // variable to store the value coming from the sensor

  // read the value from the sensor:
  sensorValue = analogRead(sPin);

  // print the value
  Serial.print("sensorValue = ");
  Serial.println(sensorValue);
  Serial.print("");
  delay(250);
}

void dontRunIntoThings() {
  int IRrangePinValue = analogRead(IRrangePin);

  if (IRrangePinValue > 300) {
    digitalWrite(redPin, HIGH);
    playNoteLength(ab5, eighthNote);
    playNoteLength(ab5, eighthNote);
    playNoteLength(ab5, eighthNote);
    leftFast(30);

    digitalWrite(redPin, LOW);
  }

  else {
    digitalWrite(greenPin, HIGH);
    playNoteLength(c4, eighthNote);
    forwardStepFast();
    digitalWrite(greenPin, LOW);
  }
}

void dancebuttons() {
  boolean forwardButtonState = digitalRead(cbuttonPin);
  boolean backwardButtonState = digitalRead(dbuttonPin);
  boolean leftButtonState = digitalRead(ebuttonPin);
  boolean rightbuttonState = digitalRead(fbuttonPin);


  if (forwardButtonState == false) {
    forwardStepFast();
    displayGreen();
  }
  if (backwardButtonState == false) {
    backwardStepFast();
    displayPurple();
  }
  if (leftButtonState == false) {
    leftStepFast();
    displayOrange();
  }
  if (rightbuttonState == false) {
    rightStepFast();
    displayWhite();
  }
}




