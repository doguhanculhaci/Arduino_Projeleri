# BT_gps_alzheimer_prototip

## Devre Şeması
![image](https://user-images.githubusercontent.com/53540561/117151707-025f6900-adc2-11eb-98b8-54299222523e.png)

## Açıklama
Bu proje sadece veri akışını test etmek için BT modülü ile yapılmıştır. Normalde bir SIM kartı modülü ile çok daha üst düzeyde bir projedir. Sizde bu kodları temel alarak SIM kartı modülüne uyarlayabilirsiniz.


## Arduino Kodları
```
#include "SoftwareSerial.h"
#include <Wire.h>
#include <TinyGPS++.h>

static const int RXPin = 4, TXPin = 3;  //tx = 4 , rx = 3
static const uint32_t GPSBaud = 9600;

SoftwareSerial ss(RXPin, TXPin);
TinyGPSPlus gps;

String readString;

bool kullanici_kapatti = true;

void setup() {
 
  Serial.begin(9600);     

  Serial.begin(9600);
  ss.begin(GPSBaud);
  
}

void loop() {

  delay(500);
  
  if(!kullanici_kapatti)
  {
    gps_veri();
  }
  
  veri_alma();
}


void veri_alma()
{
  while (Serial.available()) 
  {
    delay(3);  
    char c = Serial.read();
    readString += c; 
  }
  if (readString.length() >0) 
  {
    Serial.print("GELEN EMİR = ");
    Serial.println(readString);
    
    if (readString == "ac")     
    {
      Serial.print("GPS SISTEMI AKTIF DURUMA GETIRILDI. ");
      kullanici_kapatti = false;
    }
    if (readString == "kapat")     
    {
      Serial.print("GPS SISTEMI PASIF DURUMA GETIRILDI. ");
      kullanici_kapatti = true;
    }
    readString="";
  } 
}

void gps_veri()
{
  while (ss.available() > 0)
  {
   if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        Serial.print(F("Konum :  "));
        float enlem = gps.location.lat();
        Serial.print(enlem, 4);
        delay(750);
        Serial.print(F(","));
        float boylam = gps.location.lng();
        Serial.println(boylam, 4);
        delay(750);
      }
    } 
  }
}
```
