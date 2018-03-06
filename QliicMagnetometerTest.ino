// QliicMagnetometerTest.ino

#include <QliicMagnetometer.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  lcd.init();
  lcd.backlight();

    magnetometerSetup();

    if (magnetometer) {
        String readString = "magnetometer HMC5883 @ 30"; 
        
        Serial.println(readString);
        lcd.clear();
        lcd.print(readString);
        delay(1000);
    }
}


void loop() {
  String readString;
  
  if (magnetometer) {
    readString = magnetometerRead();
  
    Serial.println(readString);
    lcd.clear();
    lcd.print(readString.substring(0,15));
    lcd.setCursor(0,1);
    lcd.print(readString.substring(16,32));
    delay(100);
  }
}
