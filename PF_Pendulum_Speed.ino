// PF Laser and Light Sensor sketch by c.d.odom on 2.14.22
// PF Pendulum Speed additions on 5.1.23

int lightPin = A0;
int lightThreshold = 27;  // The trigger value between a blocked and unblocked sensor.
float diameter = 25.41;       // diameter of the pendulum in millimeters
int ledPin = 13;          // The pin number for the onboard LED

void setup()
{
  Serial.begin(9600);   // sets the comms port
  pinMode(lightPin, INPUT);
  pinMode(ledPin, OUTPUT);
  delay(250);
//printSensor();   // call the printSensor function!
}

void loop()
{
  // Grab the initial laser reading and store it in a variable:
  int lightReading = analogRead(lightPin);

  // print the light reading value:
  // Serial.print("light reading #1 = ");
  // Serial.println(lightReading);

  Serial.println("*** Ready to release the pendulum... ***");

  // while the laser is NOT blocked, wait...
  while (lightReading < lightThreshold) {
    // get a new sensor reading:
    lightReading = analogRead(lightPin);

    // print the sensor value to prove the while-loop is looping:
    // Serial.println(lightReading);
  }  // end of while-loop #1

  // the laser beam must have been interrupted, so
  // grab the initial time from the RTC:
  float initialTime = millis(); // units are in milliseconds

  // print the initial time:
  Serial.print("Initial Time = ");
  Serial.print(initialTime);
  Serial.println(" ms");

  // *****************************************
  // waiting for pendulum to exit the beam...
  // *****************************************

  // Grab a new laser reading and store it:
  lightReading = analogRead(lightPin);

  // print the light reading value:
  // Serial.print("light reading #2 = ");
  // Serial.println(lightReading);

  // while the laser is BLOCKED, wait...
  while (lightReading > lightThreshold) {
    // turn ON the onboard LED:
    digitalWrite(ledPin, HIGH);

    // get a new sensor reading:
    lightReading = analogRead(lightPin);
  }     // end of while-loop #2

  // turn OFF the onboard LED:
  digitalWrite(ledPin, LOW);

  // next, read the final time:
  float finalTime = millis(); // units are in milliseconds

  // print the final time:
  Serial.print("Final Time = ");
  Serial.print(finalTime);
  Serial.println(" ms");


  // calculate the pendulum’s elapsed time:
  float elapsedTime = finalTime - initialTime;

  // print the elapsed time:
  Serial.print("Elapsed Time = ");
  Serial.print(elapsedTime);
  Serial.println(" ms");

  // Calculate the pendulum's speed at the bottom of the swing.
  // This is NOT velocity because we do not know its direction!
  float speed = diameter / elapsedTime;      // units: mm/ms or m/s!

  // Calculate the pendulum's experimental initial height 
  // at the top of the swing.
  float initialHeight = pow(speed, 2) / (2.0 * 9.80);      // units: m!

  // Calculate the percent difference between the measured and 
  // calculated initial heights
  float measuredInitialHeight = 0.04345;            // in meters; used edge of Rubik's Cube as starting point!
  float percentDiff = 100.0 * abs(measuredInitialHeight-initialHeight) / ( (measuredInitialHeight+initialHeight)/2.0 );

  // print the speed, initial heights, and % difference:
  Serial.print("Pendulum speed = ");
  Serial.print(speed, 3);
  Serial.println(" m/s");
  Serial.print("Calculated initial height = ");
  Serial.print(initialHeight, 3);
  Serial.println(" m");
//  Serial.print("Measured initial height = ");
//  Serial.print(measuredInitialHeight, 5);
//  Serial.println(" m");
//  Serial.print("Percent Difference = ");
//  Serial.print(percentDiff, 3);
//  Serial.println(" %");
  Serial.println("==========================================");
  Serial.println("");


}   // end of the loop() function


void printSensor() {
  while (true) {
    int lightReading = analogRead(lightPin);
    Serial.println(lightReading);
    delay(500);
  }
}
