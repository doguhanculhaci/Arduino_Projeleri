#include <Wire.h>
void setup()
{
  Serial.begin (9600);
  Serial.println ("I2C Ekran türü taranıyor...");
  Wire.begin();
  for (byte e = 8; e < 150; e++)
  {
    Wire.beginTransmission (e);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("İletişim yolu bulundu,  Ekran Türü : ");
      Serial.print (e, DEC);
      Serial.print (" (0x");
      Serial.print (e, HEX);
      Serial.println (")");
    }
  }
  Serial.println ("Tamamlandı. ");
}

void loop() {}
