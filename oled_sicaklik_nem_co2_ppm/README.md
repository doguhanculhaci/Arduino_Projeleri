# oled_sicaklik_nem_co2_ppm

## Devre Şeması
BAĞLANTI ŞEMASINI KAYBETMİŞİM KODLARDA Kİ PİN ATAMALARINI OKUYARAK BAĞLANTI ŞEMASINI OLUŞTURABİLİRSİNİZ.

## Açıklama
İçerisinde 3 Farklı OLED Kütüphanenin kodları bulunmaktadır. OLED'in hangi kütüphanede daha sağlıklı çalıştığını görmek için kütüphanenin test kodlarını kullanabilirsiniz. Aşağıda verilen kodlar MQ135 Hava Kalite sensörü - DHT11 sıcaklık ve nem sensörü ve OLED kullanılarak yapılmıştır. Kullanılan OLED kütüphanesi U2G8 dir.

U8G2 KÜTÜPHANESİNİN BOYUTU BÜYÜK OLDUĞUNDAN DOLAYI DOSYALARIN ARASINDA YOKTUR. BU LİNK ÜZERİNDEN İNDİREBİLİRSİNİZ;

https://github.com/olikraus/u8g2

## Arduino Kodları
```
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
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
/// 

///RGB LED
#define kirmizi 9
#define yesil 11
#define mavi 10
///

int co2ppm = 0, sicaklik=0, nem=0, dakika=0, saniye = 0;
bool dakika_guncel = false;

void ekrana_yazdir(void) {

///CO2 GÖSTERGESİ
  u8g2.setFont(u8g_font_unifont);
  u8g2.drawStr( 4, 20, "CO");
  u8g2.setFont(u8g2_font_u8glib_4_hf);
  u8g2.drawStr( 20, 20, "2");
  u8g2.setFont(u8g_font_unifont);
  u8g2.drawStr(3,35,"LEV");
  u8g2.setCursor(2,50);
  u8g2.print(co2ppm);
  u8g2.setFont(u8g2_font_u8glib_4_hf);
  u8g2.print("ppm");
  u8g2.setFont(u8g_font_unifont);
///

///DAKİKA GÖSTERGESİ
  u8g2.drawStr(56,20,"ON");
  u8g2.drawStr(48,35,"TIME");
  u8g2.setCursor(54,50);
  u8g2.print(dakika);
  u8g2.setFont(u8g2_font_u8glib_4_hf);
  u8g2.print("min");
  u8g2.setFont(u8g_font_unifont);
///

///SİCAKLİK GÖSTERGESİ
  u8g2.drawStr(95, 20, "T(C)");
  u8g2.setCursor(98,35); 
  u8g2.print(sicaklik);
///

///NEM GÖSTERGESİ
  u8g2.drawStr(98, 50, "RH%");
  u8g2.setCursor(98,63);
  u8g2.print(nem);
///

}

void setup() 
{
  Serial.begin(9600);

  u8g2.begin();

  ///RGB LED
  pinMode(kirmizi,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(mavi,OUTPUT);

  digitalWrite(kirmizi,LOW);
  digitalWrite(yesil,LOW);
  digitalWrite(mavi,LOW);
  ///

}
 
void loop() 
{
  saniye = millis()/1000;
  saniye = saniye % 60;

  if((saniye == 59 || saniye == 58) && !dakika_guncel)
  {
    dakika_guncel=true;
    dakika++;
  }

  if((saniye == 1 || saniye == 2) && dakika_guncel)
  {
    dakika_guncel = false;
  }

  
  int chk = DHT11.read(DHT11PIN);
  
  gaz_seviyesi = analogRead(mq_sensor);
  co2ppm = gaz_seviyesi - 70;
  
  co2ppm = map(co2ppm,0,1023,400,4000);
      
  Serial.print("CO2: ");
  Serial.print(co2ppm);
  Serial.println("ppm");

  ///DHT11
  sicaklik = DHT11.temperature;
  nem = DHT11.humidity;
  
  Serial.print("Sicaklik: "); 
  Serial.print(sicaklik); 
  Serial.print("C, Nem: "); 
  Serial.println(nem); 
  ///

  if(co2ppm <= 925)
  {
    Serial.println("YESİL RENK");
    digitalWrite(kirmizi,0);
    digitalWrite(yesil,255);
    digitalWrite(mavi,0);
  }
  else if(co2ppm > 925)
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

  u8g2.firstPage();
  do {
    ekrana_yazdir();
  } while ( u8g2.nextPage() );
 
  delay(1000);
}
```
