// QliicMagnetometer.h

#include <Wire.h>

//boolean magnetometer = false;
//int magnetometerAxeX, magnetometerAxeY, magnetometerAxeZ, magnetometerDegre;

String magnetometerRead(){
    
  const int address=30; //0x1E;
  int x,y,z; //triple axis data
  int xmin,xmax,ymin,ymax,zmin,zmax;
  xmin=0; xmax=0; ymax=0; ymin = 0; zmin=0;zmax=0;

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    z = -z; //inversion du module
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  magnetometerAxeX = x;
  magnetometerAxeY = y;
  magnetometerAxeZ = z;

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  
  float heading = atan2(y, x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  
  float headingDegrees = heading * 180/M_PI; 
  
  //Serial.println(headingDegrees);

  int degre = (int) headingDegrees;

  magnetometerDegre = degre;
  
  char buf[80];
  sprintf(buf,"d:%i,x:%i,y:%i,z:%i",degre, x, y, z);
  return buf;

}

void magnetometerSetup() {
  String message;
  
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  const int address=30; //0x1E
  
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  int error = Wire.endTransmission();

  if (error == 0) {
    magnetometer = true;
  }
}
