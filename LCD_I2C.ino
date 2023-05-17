/*
  LCD_I2C.ino
  c.d.odom on 6.13.20
  boards:
  16x2: https://www.amazon.com/dp/B00VC2NEU8
  20x4: https://www.amazon.com/dp/B01GPUMP9C?th=1

  There are two ways to install the Liquid Crystal library:
    1. Tools >> Manage Libraries, then search for "LiquidCrystal I2C" by Frank de Brabander, then click Install.
    2. My students can download the LiquidCrystal_I2C-master.zip file from my Canvas tile:
          Canvas >> Files >> Modules and Libraries >> LiquidCrystal_I2C-master.zip.
          Download it to your Modules folder as a ZIP (Mac users may need to re-compress it).
          Then from the Arduino IDE, Sketch >> Include Libraries >> Add Zip Libraries

  Make sure to adjust the contrast using a screwdriver on the back of the daughter board

  Help setting up the LCD: https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/

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

#include <LiquidCrystal_I2C.h>

// 16x2.  Address = 0x27.   Name = lcd.
// This is for a 16 chars x 2 line display
// Usual LCD address 0x27. 0x3F is another common address (e.g. LAFVIN). 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// 20x4.  Address = 0x27.   Name = lcd2.
// This is for a 20 chars x 4 line display
// Usual LCD address 0x27. 0x3F is another common address (e.g. LAFVIN). 
// If A2 jumper is soldered, e.g., address is 0x23.   
//LiquidCrystal_I2C lcd2(0x23, 20, 4); 


// Uncomment to use the ALTERNATE I2C pins on Teensy 3.x (necessary if you are NOT using default SDA and SCL pins!)
//int SDApin = 17;     // A3. Only necessary if you are are using ALTERNATE SDA and SCL pins on Teensy 3.x!
//int SCLpin = 16;     // A2. Only necessary if you are are using ALTERNATE SDA and SCL pins on Teensy 3.x!


void setup() {
  Serial.begin(9600);
  while (!Serial);      // pause until the Serial Monitor is opened...
  delay(250);

  // uncomment the following to use ALTERNATE I2C pins:
//    Wire.setSDA(SDApin);     // Only necessary if you are are using ALTERNATE SDA and SCL pins!
//    Wire.setSCL(SCLpin);     // Only necessary if you are are using ALTERNATE SDA and SCL pins!

  Serial.println("Initialize LCD and print welcome message...");

  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2, 0);    // col, row
  lcd.print("Hello world!");
  lcd.setCursor(2, 1);
  lcd.print("Start me up!");
  delay(3000);
}

void loop() {
  Serial.println("Print the time...");

  lcd.clear();
  lcd.setCursor(0, 0);    // col, row
  lcd.print("millis = ");
  lcd.setCursor(9, 0);    // col, row
  lcd.print(millis());
  delay(1000);

}
