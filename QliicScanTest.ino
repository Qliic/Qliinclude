// QliicScanTest.ino

#include <Wire.h>
#include <QliicScan.h>
  
void setup(){
  Serial.begin(115200);
  setupDetecterI2C();
}
 
void loop() {
  detecterI2C();
}
