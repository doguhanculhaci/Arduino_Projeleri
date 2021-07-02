#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Fonts/FreeMonoBold18pt7b.h> 

Adafruit_SSD1306 display(128, 64);           
Adafruit_MLX90614 mlx = Adafruit_MLX90614();  

float okuma[30];
float toplam ;
float sicaklik ;
int buton_durum;
float deger;
int buton=6;

#include "SoftwareSerial.h"
#include <Wire.h>
String readString;

void buton_kontrol()
{
  buton_durum = digitalRead(buton);

  if (buton_durum == 1)
  {
    //Serial.println("ateş ölçülüyor");
    ates_olcme();
  }
  else
  {
    //Serial.println("ölçülmedi");
    display.clearDisplay(); 
    display.setFont();
    display.setCursor(10,10);  // (x,y)
    display.println("AD SOYAD");  
    display.setCursor(10,40);  // (x,y) 
    display.println("OKUL NUMARASI");  
    display.display();
  }
}

void ates_olcme()
{
  //Serial.println("ateş ölçüldü");
  toplam=0;
  
  for (int i=0; i<30; i++)
  {
    deger =mlx.readObjectTempC();
    okuma[i]= deger *1;
    toplam = toplam + okuma[i];
    delay (5);
  }
  
  sicaklik = toplam / 30.0;

  display.clearDisplay(); 
  display.setFont();
  display.setCursor(10,10);  // (x,y)
  display.println("VUCUT SICAKLIGINIZ");  // Text or value to print
  display.setCursor(14,2);  // (x,y)
  display.println(".");  // Text or value to print
  display.setCursor(17,2);  // (x,y)
  display.println(".");  // Text or value to print
  display.setCursor(88,4);  // (x,y)
  display.println("-");  // Text or value to print
  
  display.setFont(&FreeMonoBold18pt7b);  // Set a custom font
  display.setCursor(10,55);  // (x,y)
  display.println(sicaklik,1);
   display.setCursor(100,55);  // (x,y)
  display.println("C");  // Text or value to print
  display.setCursor(88,37);  // (x,y)
  display.println(".");  // Text or value to print
  display.display();
  
  Serial.print(sicaklik); 

  delay(3000);
}

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay(); 
  display.setTextColor(WHITE);  
  mlx.begin();  

  pinMode(buton,INPUT);

  Serial.begin(9600);
}

void loop() {

  buton_kontrol();
  
  veri_alma();
}


void veri_alma()
{
  while (Serial.available()) 
  {
    //Serial.println("VERİ GELDİ");
    delay(3);  
    char c = Serial.read();
    readString += c; 
  }
  if (readString.length() >0) 
  {
    if (readString == "oku")     
    {
      //Serial.println("VERİ OKUNDU");
      ates_olcme();
    }
    readString="";
  } 
}
