/* servoMotionModule.ino
   Wheeled robot servo module
   by C.D.Odom on 2.17.2015
*/

/*
************************************************************************
**          COPY EVERYTHING BELOW INTO YOUR MAIN SKETCH               **
************************************************************************

// GLOBALS
const int leftServoPin = 0;               // servo pin for LEFT wheel
const int rightServoPin = 1;              // servo pin for RIGHT wheel
const int LEDPin = 13;                    // the onboard LED pin (for diagnostics)

void setup() {
  pinMode(leftServoPin, OUTPUT);
  pinMode(rightServoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  blinkOK(3);                // a diagnostic tool to let user know all is OK
}

************************************************************************
**          COPY EVERYTHING ABOVE INTO YOUR MAIN SKETCH               **
************************************************************************
*/

// Left Servo Pulse Width Constants 
const int left_forward_fast = 2000;       // CCW Fast
const int left_forward_slow = 1600;       // CCW Slow
const int left_stop = 1500;               // Center position
const int left_reverse_slow = 1400;       // CW Slow
const int left_reverse_fast = 1000;       // CW Fast

// Right Servo Pulse Width Constants 
const int right_forward_fast = 1000;      // CW Fast
const int right_forward_slow = 1400;      // CW Slow
const int right_stop = 1500;              // Center position
const int right_reverse_slow = 1600;      // CCW Slow
const int right_reverse_fast = 2000;      // CCW Fast


void blinkOK(int numBlinks) {
  // blink the onboard LED to let the user know the code was properly uploaded
  for (int i = 0; i < numBlinks; i++) {
    digitalWrite(LEDPin, HIGH);
    delay(500);
    digitalWrite(LEDPin, LOW);
    delay(500);
  }
}

void motionFastTest() {
  // a diagnostic test of basic robot motion at high speed
  forwardFast(88);      // move forward with 88 quick "steps" (about xxx cm with my OneBot)
  robotStop(10);        // give the motors time to stop; prevents high current drain
  leftFast(50);         // pivot 50 quick "steps" to the left (about 180 degrees with my OneBot)
  robotStop(10);        
  forwardFast(88);      // return to starting point
  robotStop(10);        
  rightFast(100);       // pivot about 360 degrees to the right
  robotStop(10);        
  reverseFast(88);      // move in reverse with 88 quick "steps" (about xxx cm with my OneBot)
}

void motionSlowTest() {
  // a diagnostic test of basic robot motion at slow speed
  forwardSlow(88);      // move forward with 100 slow "steps" (about xxx cm with my OneBot)
  robotStop(10);        // give the motors time to stop; prevents high current drain
  leftSlow(100);        // pivot 100 slow "steps" to the left (about 180 degrees with my OneBot)
  robotStop(10);        
  forwardSlow(88);      // return to starting point
  robotStop(10);        
  rightSlow(200);       // pivot about 360 degrees to the right
   robotStop(10);        
  reverseSlow(88);      // move in reverse with 50 slow "steps" (about xxx cm with my OneBot)
}



// These movement functions are the HIGHEST LEVEL commands. They cause the robot to 
// take a certain number of steps in the designated direction and speed, or to stop 
// for a certain number of "steps". These functions call the "step" functions below.  

void robotStop(int x) {
  for (int i = 0; i <= x ; i++) {
    stopStep();     // a hard stop (not a coasting stop)
  }
}

void forwardFast(int x) {
  for (int i = 0; i <= x ; i++) {
    forwardStepFast();
  }
}

void forwardSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    forwardStepSlow();
  }
}

void reverseFast(int x) {
  for (int i = 0; i <= x ; i++) {
    reverseStepFast();
  }
}

void reverseSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    reverseStepSlow();
  }
}

void rightFast(int x) {
  for (int i = 0; i <= x ; i++) {
    rightStepFast();
  }
}

void rightSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    rightStepSlow();
  }
}

void leftFast(int x) {
  for (int i = 0; i <= x ; i++) {
    leftStepFast();
  }
}

void leftSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    leftStepSlow();
  }
}


// These "step" functions are the SECOND LOWEST LEVEL of the movement commands. They are
// used to turn both servo wheels in concert to make the robot take exactly one step in
// some direction, or to send a hard stop to both wheels.  This is done by calling the
// createPulse() function, once for each wheel. It is CRITICAL that you keep the 20ms 
// delay, because it is necessary to give the motors time to respond!

void stopStep() {
  createPulse(leftServoPin, left_stop);
  createPulse(rightServoPin, right_stop);
  delay(20);      // do NOT alter this delay time!      
}

void forwardStepFast() {
  createPulse(leftServoPin, left_forward_fast);
  createPulse(rightServoPin, right_forward_fast);
  delay(20);      // do NOT alter this delay time!      
}

void forwardStepSlow() {
  createPulse(leftServoPin, left_forward_slow);
  createPulse(rightServoPin, right_forward_slow);
  delay(20);      // do NOT alter this delay time!
}

void reverseStepFast() {
  createPulse(leftServoPin, left_reverse_fast);
  createPulse(rightServoPin, right_reverse_fast);
  delay(20);      // do NOT alter this delay time!
}

void reverseStepSlow() {
  createPulse(leftServoPin, left_reverse_slow);
  createPulse(rightServoPin, right_reverse_slow);
  delay(20);      // do NOT alter this delay time!
}

void rightStepFast() {
  createPulse(leftServoPin, left_forward_fast);
  createPulse(rightServoPin, right_reverse_fast);
  delay(20);      // do NOT alter this delay time!
}

void rightStepSlow() {
  createPulse(leftServoPin, left_forward_slow);
  createPulse(rightServoPin, right_reverse_slow);
  delay(20);      // do NOT alter this delay time!
}

void leftStepFast() {
  createPulse(leftServoPin, left_reverse_fast);
  createPulse(rightServoPin, right_forward_fast);
  delay(20);      // do NOT alter this delay time!
}

void leftStepSlow() {
  createPulse(leftServoPin, left_reverse_slow);
  createPulse(rightServoPin, right_forward_slow);
  delay(20);      // do NOT alter this delay time!
}


// createPulse() is the LOWEST LEVEL (most basic) of the movement commands.
// It simply creates a single pulse of a given pulse width on a given pin.
// This command makes ONE servo (set by the servoPin variable) take ONE 
// step whose speed and direction is set by the pulseWidth variable. 

void createPulse(byte servoPin, int pulseWidth) {
  // take one step with one servo
  digitalWrite(servoPin, HIGH);        // create the rising edge of the pulse
  delayMicroseconds(pulseWidth);       // precisely set pulse width in microseconds!
  digitalWrite(servoPin, LOW);         // create the falling edge of the pulse
}
