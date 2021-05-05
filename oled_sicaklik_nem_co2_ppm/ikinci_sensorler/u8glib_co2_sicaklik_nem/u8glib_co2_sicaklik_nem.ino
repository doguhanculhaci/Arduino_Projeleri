///DHT11.
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 2 // DHT11PIN olarak Dijital 2"yi belirliyoruz.

dht11 DHT11;
///

///MQ135.
#define mq_sensor A0
int gaz_seviyesi = 0;
///

///OLED Kütüphanaleri eklendi.
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0); 
/// 

///RGB LED
#define kirmizi 9
#define yesil 11
#define mavi 10
///

int sicaklik=0, nem=0;

void ekrana_yazdir(void) {
   
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 2, 20, "CO2: ");
  u8g.setPrintPos(45, 20); 
  u8g.print(gaz_seviyesi);
  u8g.print(" ppm");
  
  u8g.drawStr( 2, 40, "Temperature: ");
  u8g.setPrintPos(100, 40); 
  u8g.print(sicaklik);
  u8g.print("C");

  u8g.drawStr( 2, 60, "Humidity: ");
  u8g.setPrintPos(85, 60); 
  u8g.print(nem);
  u8g.print("%");
}

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
  pinMode(8, OUTPUT);
  
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  ///
  
}
 
void loop() 
{
  int chk = DHT11.read(DHT11PIN);
  
  gaz_seviyesi = analogRead(mq_sensor);
      
  Serial.print("CO2: ");
  Serial.println(gaz_seviyesi);
  Serial.print("ppm");

  ///DHT11
  sicaklik = DHT11.temperature;
  nem = DHT11.humidity;
  
  Serial.print("Sicaklik: "); 
  Serial.print(sicaklik); 
  Serial.print("C, Nem: "); 
  Serial.println(nem); 
  ///

  if(gaz_seviyesi < 800)
  {
    Serial.println("YESİL RENK");
     digitalWrite(kirmizi,0);
    digitalWrite(yesil,255);
    digitalWrite(mavi,0);
  }
  else if(gaz_seviyesi >= 800 && gaz_seviyesi <= 975)
  {
    Serial.println("SARI-TURUNCU RENK");
    digitalWrite(kirmizi,0);
    digitalWrite(yesil,0);
    digitalWrite(mavi,255);
  }
  else if(gaz_seviyesi > 975)
  {
    Serial.println("KIRMIZI RENK");
    digitalWrite(kirmizi,255);
    digitalWrite(yesil,255);
    digitalWrite(mavi,0);
  }
  else
  {
    Serial.println("ÜRETİLEN DEĞER HATALI");
    digitalWrite(kirmizi,LOW);
    digitalWrite(yesil,LOW);
    digitalWrite(mavi,LOW);
  }

   u8g.firstPage();  
   do {
      ekrana_yazdir();
    } while( u8g.nextPage() );
 
  delay(1000);
}
