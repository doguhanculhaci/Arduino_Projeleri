///AHT10 Kütüphanaleri eklendi.
#include <Adafruit_AHT10.h>
Adafruit_AHT10 aht;
///

///CJMCU-811 Kütüphanaleri eklendi.
#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;
///

///OLED Kütüphanaleri eklendi.
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    
#define SCREEN_HEIGHT 64  
#define OLED_RESET -1
       
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/// 

///RGB LED
#define kirmizi 9
#define yesil 10
#define mavi 11
///
 
void setup() 
{
  Serial.begin(9600);

  ///RGB LED
  pinMode(kirmizi,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(mavi,OUTPUT);

  digitalWrite(kirmizi,LOW);
  digitalWrite(yesil,LOW);
  digitalWrite(mavi,LOW);
  ///

  ///OLED Kurulumu yapıldı.
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //OLED I2C adresi 0x3C (128x64)
  delay(500);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25, 15);
  display.println("Sistem Kurulumu");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Baslatiliyor");
  display.display();
  ///
  
  ///CJMCU-811 Kurulumu yapıldı.
  if (!ccs.begin()) 
  {
    Serial.println("CJMCU-811 Kablolarini kontrol ediniz.");
    while (1);
  }
 
  // Wait for the sensor to be ready
  while (!ccs.available())
  {
    Serial.println("CJMCU-811 ILETISIMI BEKLENIYOR.");
  }
  ///
  
  ///AHT10 Kurulumu yapıldı.
  if (! aht.begin()) {
    Serial.println("AHT10 Kablolari kontrol ediniz.");
    while (1);
  }
  ///
}
 
void loop() 
{
  ///CJMCU-811
  if (ccs.available()) 
  {
    if (!ccs.readData()) 
    {
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
 
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("CO2:");
      display.print(ccs.geteCO2());
      display.setTextSize(1);
      display.print(" ppm");

      if(ccs.geteCO2()<1000)
      {
        Serial.println("YESİL RENK");
        digitalWrite(kirmizi,LOW);
        digitalWrite(yesil,HIGH);
        digitalWrite(mavi,LOW);
      }
      else if(ccs.geteCO2()>=1000 && ccs.geteCO2()<=1300)
      {
        Serial.println("SARI-TURUNCU RENK");
        digitalWrite(kirmizi,255);
        digitalWrite(yesil,185);
        digitalWrite(mavi,15);
      }
      else if(ccs.geteCO2()>1300)
      {
        Serial.println("KIRMIZI RENK");
        digitalWrite(kirmizi,HIGH);
        digitalWrite(yesil,LOW);
        digitalWrite(mavi,LOW);
      }
      else
      {
        Serial.println("ÜRETİLEN DEĞER HATALI");
        digitalWrite(kirmizi,LOW);
        digitalWrite(yesil,LOW);
        digitalWrite(mavi,LOW);
      }
 
    }
    else 
    {
      Serial.println("CJMCU-811 ERROR!");
      
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 5);
      display.print("ERROR!");
      while (1);
    }

    ///AHT10
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp); // Veriler güncellendi.
  
    Serial.print("Sicaklik: "); 
    Serial.print(temp.temperature); //Serial.println(" degrees C");
    Serial.print("C, Nem: "); 
    Serial.println(humidity.relative_humidity); //Serial.println("% rH");
     
    display.setTextSize(2);
    display.setCursor(0, 40);
    display.print("Sicaklik:");
    display.print(temp.temperature);
    display.setTextSize(1);
    display.print(" C");
 
    display.setTextSize(2);
    display.setCursor(0, 60);
    display.print("Nem: ");
    display.setTextSize(1);
    display.print("%");
    display.print(humidity.relative_humidity);
    display.display();
    ///
  }
  ///
  delay(1000);
}
