// QliicScan.h
// https://playground.arduino.cc/Main/I2cScanner
  
void setupDetecterI2C()
{
  Wire.begin();
 
  Serial.println("\nQliic : Detecter les peripheriques I2C");
}
 
String nomQliicTable (int adresseI2C) {
  String reponse;

  switch (adresseI2C) {
    case 30 : reponse = "Magnetometre"; break;
    case 39 : reponse = "Ecran LCD"; break;
    case 41 : reponse = "Detecteur de couleurs"; break;
    case 104 : reponse = "Gyroscope"; break;
    default : reponse = "I2C"; break;
  }
  
  return reponse;
}
 
void detecterI2C()
{
  byte reponseI2C, adresseI2C;
  int compteurAdresse;
  String nomQliic;
 
  compteurAdresse = 0;
  
  for(adresseI2C = 1; adresseI2C < 127; adresseI2C++ )
  {
    Wire.beginTransmission(adresseI2C);
    reponseI2C = Wire.endTransmission();
 
    if (reponseI2C == 0)
    {
      Serial.print(nomQliicTable(adresseI2C)); 
      Serial.print(" @ "); 
      Serial.println(adresseI2C); 
      compteurAdresse++;
    }
    else if (reponseI2C==4)
    {
      Serial.print("Probleme @ "); 
      Serial.println(adresseI2C);
    }    
  }
  
  if (compteurAdresse == 0)
    Serial.println("Aucun peripherique I2C");
}
