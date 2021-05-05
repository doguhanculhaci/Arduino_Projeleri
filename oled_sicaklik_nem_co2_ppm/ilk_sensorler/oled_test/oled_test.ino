///OLED Kütüphanaleri eklendi.
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    
#define SCREEN_HEIGHT 64  
#define OLED_RESET 4       
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/// 

void setup() 
{
  Serial.begin(9600);

  ///OLED Kurulumu yapıldı.
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //OLED I2C adresi 0x3C (128x64)
  delay(500);
  display.clearDisplay();
  display.setCursor(25, 15);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Sensor");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Başlatılıyor");
  display.display();
  ///
 
}
 
void loop() 
{
}
