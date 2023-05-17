/*
   Multiple i2c RTC and LCD Clock.ino by c.d.odom on 5.9.23

   Combination of two sketches:
      1. RTC_Read_Time_v4.ino by c.d.odom on 4.1.23
      2. LCD_I2C.ino by c.d.odom on 6.13.20

   Clock functions with Teensy 3.2/3.5/4.1
   using DS3231 AT24C32 RTC (I2C) module (see https://www.amazon.com/dp/B00LX3V7F0)
   with 3V coin battery (2032 lithium coin cell), which keeps time for years!!!
   uses the DS1307RTC.h library, which is installed with Teensyduino

   THIS CODE IS USED TO *READ* THE RTC CLOCKS OF THE TEENSY AND DS3231 RTC MODULE!
   To *set* the clocks, use RTC_Set_Time_v4.ino

   Time library uses a special time_t variable type, which is the number of seconds
   elapsed since 1970. Using time_t lets you store or compare times as a single number,
   rather that dealing with 6 numbers and details like the number of days in each month
   and leap years.

   see File >> Examples >> Time >> ...
   see http://playground.arduino.cc/Code/time
   use http://www.epochConverter.com to convert t to hhmmssddmmyy
   See http://www.instructables.com/id/Make-an-accurate-Arduino-clock-using-only-one-wire/ for accurate and simple time keeping using PWM!

  LCD boards:
  16x4: https://www.amazon.com/dp/B00VC2NEU8
  20x4: https://www.amazon.com/dp/B01GPUMP9C?th=1

  help setting up the LCD: https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/

  There are two ways to install the Liquid Crystal library:
    1. Tools >> Manage Libraries, then search for "LiquidCrystal I2C" by Frank de Brabander, then click Install.
    2. My students can download the LiquidCrystal_I2C-master.zip file from my Canvas tile:
          Canvas >> Files >> Modules and Libraries >> LiquidCrystal_I2C-master.zip.
          Download it to your Modules folder as a ZIP (Mac users may need to re-compress it).
          Then from the Arduino IDE, Sketch >> Include Libraries >> Add Zip Libraries

  Make sure to adjust the contrast using a screwdriver on the back of the daughter board

  You may need to check the address of the LCD using I2C_scanner.ino (if  the standard
  0x27 or 0x3F addresses don't work).

  See https://www.pjrc.com/teensy/td_libs_Wire.html,
  and https://www.pjrc.com/teensy/pinout.html


  I2C LED connections for Teensy 3.x and 4.x boards:
                LCD Pins    Arduino Pins
                ------------------------
                    GND    |     GND
                    VCC    |     5V
                    SDA    |     A4   (Teensy 3.x users may substitute with pin A3)
                    SCL    |     A5   (Teensy 3.x users may substitute with pin A2)


  For MULTIPLE I2C devices, there are a couple of options:
      - for Teensy 3.x with TWO I2C devices, simply use the Alternate SDA and 
        SCL pins (17 and 16, respectively).  Use the code below, uncommenting the 
        ALTERNATE pins below.
      - for Teensy 4.x and Teensy 3.x with more than 2 I2C devices, use my I2C Bus 
        PCB (see "I2C mother daughter connect.pcb").  This uses two 4.7k pullup resistors, one each between
        Vcc and SDA, and Vcc and SCL, as explained here:
           * https://learn.adafruit.com/working-with-i2c-devices/pull-up-resistors
           * https://learn.adafruit.com/assets/109426

  20x4 LCD address is 0x27 or 0x3F by default.  Solder the jumpers A0, A1, A2 to create new
  addresses like so:

  A0 A1 A2 ID
  0  0  0  0X27 All open (This is how mine came)    -- verified with Scanner.ino
  1  0  0  0X26 A0 only closed      -- verified with Scanner.ino
  0  1  0  0X25 A1 only closed      -- verified with Scanner.ino
  1  1  0  0x24 A0 and A1 closed    -- verified with Scanner.ino
  0  0  1  0X23 A2 only closed      -- verified with Scanner.ino
  1  0  1  0X22 A0 and A2 closed    -- verified with Scanner.ino
  0  1  1  0X21 A1 and A2 closed    -- verified with Scanner.ino
  1  1  1  0X20 All three jumpers jumped.    -- verified with Scanner.ino

*/

// ****************  RTC stuff  *****************
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

// GLOBALS for RTC
tmElements_t tm;              // RTC time data type; needed for Teensy Time and Date Method

char timeDateBuffer[25];      // Buffer array for storing date/time data to be printed using snprintf()
char timeBuffer[15];          // Buffer array for storing time data to be printed using snprintf()
char dateBuffer[15];          // Buffer array for storing date data to be printed using snprintf()


// ****************  LCD stuff  *****************
#include <LiquidCrystal_I2C.h>

// 16x2.  Address = 0x27.   Name = lcd.
// usual LCD address 0x27. 0x3F is another common address (e.g. LAFVIN). This is for a 16 chars x 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// 20x4.  Address = 0x27.   Name = lcd2.
// A2 jumper is soldered, so address is 0x23.  0x3F is another common address (e.g. LAFVIN). This is for a 20 chars x 4 line display
LiquidCrystal_I2C lcd2(0x23, 20, 4); 


// Uncomment to use the ALTERNATE I2C pins on Teensy 3.x (necessary if you are NOT using default SDA and SCL pins!)
//int SDApin = 17;     // A3. Only necessary if you are are using ALTERNATE SDA and SCL pins on Teensy 3.x!
//int SCLpin = 16;     // A2. Only necessary if you are are using ALTERNATE SDA and SCL pins on Teensy 3.x!


void setup() {
  Serial.begin(9600);

  // uncomment the following to use ALTERNATE I2C pins:
  //  Wire.setSDA(SDApin);     // Only necessary if you are are using ALTERNATE SDA and SCL pins!
  //  Wire.setSCL(SCLpin);     // Only necessary if you are are using ALTERNATE SDA and SCL pins!

  // setup the RTC:
  setupRTC();

  Serial.println("Initialize LCD and print welcome message...");

  // LCD #1:
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2, 0);    // col, row
  lcd.print("Hello LCD #1!");
  lcd.setCursor(2, 1);
  lcd.print("Start me up!");

  // LCD #2:
  lcd2.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd2.backlight();
  lcd2.setCursor(2, 0);    // col, row
  lcd2.print("Hello LCD #2!");
  lcd2.setCursor(2, 1);
  lcd2.print("Start me up!");

  delay(3000);

}


void loop() {
  // if the Real Time Clock (RTC) is able to read the time...
  if (RTC.read(tm)) {
    // ********* Teensy Time and Date Method using snprintf: ************
    // save the date and the time to a character array, then print the array
    snprintf(timeDateBuffer, 25, "%02d/%02d/%04d %02d:%02d:%02d",
             tm.Month, tm.Day, tmYearToCalendar(tm.Year),
             tm.Hour, tm.Minute, tm.Second);
    Serial.print("timeDateBuffer = ");
    Serial.println(timeDateBuffer);

    // save the time to a character array, then print the array
    snprintf(timeBuffer, 15, "%02d:%02d:%02d",
             tm.Hour, tm.Minute, tm.Second);
    Serial.print("timeBuffer = ");
    Serial.println(timeBuffer);

    // save the date to a character array, then print the array
    snprintf(dateBuffer, 15, "%02d/%02d/%04d",
             tm.Month, tm.Day, tmYearToCalendar(tm.Year));
    Serial.print("dateBuffer = ");
    Serial.println(dateBuffer);

    // LCD #1:
    lcd.clear();
    lcd.setCursor(0, 0);          // col, row
    lcd.print(dateBuffer);        // display the date
    lcd.setCursor(0, 1);
    lcd.print(timeBuffer);        // display the time
    lcd.setCursor(13, 0);
    lcd.print("LCD");
    lcd.setCursor(14, 1);
    lcd.print("1");               // LCD #1 marker

    // LCD #2:
    lcd2.clear();
    lcd2.setCursor(0,0);          // col, row
    lcd2.print("I2C RTC & Dual LCDs");   
    lcd2.setCursor(0, 1);         // col, row
    lcd2.print(timeDateBuffer);   // display the time and date
    lcd2.setCursor(17, 2);
    lcd2.print("LCD");
    lcd2.setCursor(18, 3);
    lcd2.print("2");              // LCD #2 marker

    delay(1000);
  }
  else {
    // There is some issue with the RTC.  Drat!
    errorMessageRTC();
  }
}

void setupRTC() {
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

void errorMessageRTC(){
  if (RTC.chipPresent()) {
      Serial.println("The DS3231 has stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS3231 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(5000);
}
