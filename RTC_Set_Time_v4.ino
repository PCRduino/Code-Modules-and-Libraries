/* RTC_Set_Time_v4.ino by c.d.odom on 4.1.23
   snprintf printing added on 4.15.23
   clock functions with Teensy 3.2/3.5/4.1
   using DS3231 AT24C32 RTC (I2C) module (see https://www.amazon.com/dp/B00LX3V7F0)
   with 3V coin battery (2032 lithium coin cell), which keeps time for years!!!
   uses the DS1307RTC.h library, which is installed with Teensyduino

   THIS CODE IS USED TO *SET* THE RTC CLOCKS OF THE TEENSY AND DS3231 RTC MODULE!
   To *read* the clocks, use RTC_Read_Time_v3.ino

   Time library uses a special time_t variable type, which is the number of seconds
   elapsed since 1970. Using time_t lets you store or compare times as a single number,
   rather that dealing with 6 numbers and details like the number of days in each month
   and leap years.

   see File >> Examples >> Time >> ...
   see http://playground.arduino.cc/Code/time
   use http://www.epochConverter.com to convert t to hhmmssddmmyy
   See http://www.instructables.com/id/Make-an-accurate-Arduino-clock-using-only-one-wire/ for accurate and simple time keeping using PWM!

   Teensy 3.2/3.5/4.1 connections:
       SCL to pin A5
       SDA to pin A4
       VCC to 5V
       GND to ground
*/

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

// Globals for RTC:
tmElements_t tm;              // RTC time data type; needed for Teensy Time and Date Method
char timeDateBuffer[50];         // Buffer array for storing date/time data to be printed using snprintf()


void setup() {
  Serial.begin(9600);
  while (!Serial);     // wait until Serial Window is opened.  OK to have this, as the laptop will be connected when time is set!

  // a test of raw time conversion
  //  convertRawTime(1357041600);    // should be noon Jan 1 2013
  //  convertRawTime(1546300800);    // should be midnight Jan 1 2019

  // set the time -- there are two ways: hard code with code (loadUserTime() = fastest, good for testing),
  // or serial monitor input using SKIF functions (loadUserTimeSKIF() = slowest, but best for precision setting!).
  // Time must be entered as follows:
  // (hr, min, sec, day, mo, yr (yyyy), weekday (0-6))
  // !!! the weekday function is not working as of 4.2.23 !!!

  //  loadUserTime(11, 15, 0, 2, 4, 2023, 0);
  //  loadUserTime(0, 0, 0, 1, 1, 1970, 0);
  //  loadUserTime(1, 0, 0, 1, 1, 1970, 0);
  //  loadUserTime(23, 59, 50, 1, 1, 1970, 0);
  //  loadUserTime(0, 0, 0, 2, 2, 1970, 0);
  //  loadUserTime(0, 0, 0, 1, 1, 1971, 0);
  //  loadUserTime(23, 59, 50, 31, 12, 1970, 0);
  //  loadUserTime(11, 15, 0, 2, 4, 2023, 0);

  loadUserTimeSKIF();


  // make sure the DS3231 RTC Module is connected, powered, and operating properly:
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) {
    while (true) {
      Serial.println("Unable to sync with the RTC");
      delay(1000);
    }
  }
  else {
    Serial.println("RTC has set the system time");
  }
}


void loop() {
  // print the raw date/time value:
  // Serial.println(now());        // print the RAW time, or time_t number type

  if (RTC.read(tm)) {
    // ********* Teensy Time and Date Method: ************
    // brute force printing
    Serial.print("Time = ");
    print2digits(tm.Hour);
    Serial.print(":");
    print2digits(tm.Minute);
    Serial.print(":");
    print2digits(tm.Second);
    Serial.print(", Date (M/D/Y) = ");
    Serial.print(tm.Month);
    Serial.print("/");
    Serial.print(tm.Day);
    Serial.print("/");
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.print(", ");
    Serial.print(tm.Wday);
    Serial.println();

    // snprintf printing:
    snprintf(timeDateBuffer, 50, "%02d/%02d/%04d @ %02d:%02d:%02d", tm.Month, tm.Day, tmYearToCalendar(tm.Year), tm.Hour, tm.Minute, tm.Second);       // practically guaranteed random name each time! filename = "j" + millis + ".txt"
    Serial.print("timeDateBuffer = ");
    Serial.println(timeDateBuffer);


    // ************ Arduino Time and Date Method: *************
    // print the date:
    Serial.print(month());
    Serial.print(".");
    Serial.print(day());
    Serial.print(".");
    Serial.print(year());
    Serial.print("    ");

    // print the time:
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.println("");


    delay(1000);
  }
  else {
    if (RTC.chipPresent()) {
      Serial.println("The DS3231 has stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS3231 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}


void loadUserTime(byte startHr, byte startMin, byte startSec, byte startDay, byte startMo, int startYr, byte startWeekDay) {
  // set the Teensy RTC to this time:
  setTime(startHr, startMin, startSec, startDay, startMo, startYr);

  //  re-convert and print this raw start time to time elements (as a sanity check)
  convertRawTime (now());

  // create a time elements array
  tmElements_t myTimeElements = {startSec, startMin, startHr, startWeekDay, startDay, startMo, startYr - 1970};   // subtract the epoch start year

  // create the raw time for Teensy time
  time_t rawTime = makeTime(myTimeElements);

  // echo the raw date/time value (as another sanity check):
  Serial.println("rawtime = " + String(rawTime));

  // set the DS3231 RTC Module clock to the time
  RTC.set(rawTime);
}


void loadUserTimeSKIF() {
  int startHr;
  int startMin;
  int startSec;
  int startDay;
  int startMo;
  int startYr;
  int startDoW;

  // use the Serial Window to set the clock
  Serial.println("^^^ Enter the start time and date \nin the above serial port textbox... \n");
  Serial.print("Enter the start DAY (1-31): ");
  startDay = readInt();
  Serial.println(startDay);
  Serial.print("Enter the start MONTH (1-12): ");
  startMo = readInt();
  Serial.println(startMo);
  Serial.print("Enter the start YEAR (YYYY): ");
  startYr = readInt();
  Serial.println(startYr);
  Serial.print("Enter the start HOUR (0-23): ");
  startHr = readInt();
  Serial.println(startHr);
  Serial.print("Enter the start MINUTE (0-59): ");
  startMin = readInt();
  Serial.println(startMin);
  Serial.print("Enter the start SECOND (0-59): ");
  startSec = readInt();
  Serial.println(startSec);
  Serial.print("Enter the start DAY of the Week (0-6): ");
  startDoW = readInt();
  Serial.println(startDoW);

  Serial.println("\nType in any letter into the textbox and \npress ENTER precicely when you are \nready to START the clock...");
  int goTime = readByte();        // just a dummy variable to wait for user to press enter to start clock

  // format: (hr, min, sec, day, mo, yr (yyyy), weekday (0-6))
  // !!! the weekday function is not working as of 4.2.23 !!!
  loadUserTime(startHr, startMin, startSec, startDay, startMo, startYr, startDoW);
  //  loadUserTime(startHr, startMin, startSec, 2, 4, 2023, 0);     // junk date data to keep from having to enter it!
}


void convertRawTime(unsigned long rawTime) {
  setTime(rawTime);

  // echo the raw date/time value:
  Serial.println("RAW TIME = " + String(rawTime));

  // print now():
  Serial.println("NOW = " + String(now()));

  // print the user date:
  Serial.println("Converted Time: ");

  Serial.print(month());
  Serial.print(".");
  Serial.print(day());
  Serial.print(".");
  Serial.print(year());
  Serial.print("    ");

  // print the time:
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.println("");
}
