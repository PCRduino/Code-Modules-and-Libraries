/* RTC_Read_Time_v4.ino by c.d.odom on 4.1.23
   snprintf print added on 4.15.23
   clock functions with Teensy 3.2/3.5/4.1
   using DS3231 AT24C32 RTC (I2C) module (see https://www.amazon.com/dp/B00LX3V7F0)
   with 3V coin battery (2032 lithium coin cell), which keeps time for years!!!
   uses the DS1307RTC.h library, which is installed with Teensyduino

   THIS CODE IS USED TO *READ* THE RTC CLOCKS OF THE TEENSY AND DS3231 RTC MODULE!
   To *set* the clocks, use RTC_Set_Time_v3.ino

   Time library uses a special time_t variable type, which is the number of seconds
   elapsed since 1970. Using time_t lets you store or compare times as a single number,
   rather that dealing with 6 numbers and details like the number of days in each month
   and leap years.

   see File >> Examples >> Time >> ...
   see http://playground.arduino.cc/Code/time
   use http://www.epochConverter.com to convert t to hhmmssddmmyy
   See http://www.instructables.com/id/Make-an-accurate-Arduino-clock-using-only-one-wire/ for accurate and simple time keeping using PWM!

  I2C LED connections for Teensy 3.x and 4.x boards:
                LCD Pins    Arduino Pins
                ------------------------
                    GND    |     GND
                    VCC    |     5V
                    SDA    |     A4   (Teensy 3.x users may substitute with pin A3)
                    SCL    |     A5   (Teensy 3.x users may substitute with pin A2)


  For MULTIPLE I2C devices, there are a couple of options:
      - for Teensy 3.x with TWO I2C devices, simply use the Alternate SDA and 
        SCL pins (17 and 16, respectively).  Use the parts of the code in "LCD_I2C.ino", 
        that involve uncommenting the ALTERNATE pins code.
      - for Teensy 4.x and Teensy 3.x with more than 2 I2C devices, use my I2C Bus 
        PCB (see xxx).  This uses two 4.7k pullup resistors, one each between
        Vcc and SDA, and Vcc and SCL, as explained here:
           * https://learn.adafruit.com/working-with-i2c-devices/pull-up-resistors
           * https://learn.adafruit.com/assets/109426

*/

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

// GLOBALS for RTC
tmElements_t tm;              // RTC time data type; needed for Teensy Time and Date Method
char timeDateBuffer[50];         // Buffer array for storing date/time data to be printed using snprintf()


void setup() {
  Serial.begin(9600);

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
  Serial.println(now());        // print the RAW time, or time_t number type

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
    snprintf(timeDateBuffer, 50, "%02d/%02d/%04d %02d:%02d:%02d", tm.Month, tm.Day, tmYearToCalendar(tm.Year), tm.Hour, tm.Minute, tm.Second);       // practically guaranteed random name each time! filename = "j" + millis + ".txt"
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

// function for RTC code
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
