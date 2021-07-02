#include<SoftwareSerial.h>
SoftwareSerial bt_iletisim(0, 1);
#define sol_ileri 8
#define sol_geri 9
#define sol_hiz 10
#define sag_ileri 13
#define sag_geri 12
#define sag_hiz 11

int motorlar_hiz = 255;
byte son_islem;

#include <dht11.h>
#define DHT11PIN 2 

dht11 DHT11;

int gaz_pin = A0, gaz_deger = 0;

bool reset = false, sicaklik_durum = false, nem_durum = false, gaz_durum = false;

void setup()
{
 pinMode(sol_ileri, OUTPUT);
 pinMode(sag_ileri, OUTPUT);
 pinMode(sol_geri, OUTPUT);
 pinMode(sag_geri, OUTPUT);
 pinMode(sol_hiz, OUTPUT);
 pinMode(sag_hiz, OUTPUT);
 //Serial.begin(9600);
 bt_iletisim.begin(9600);
}
void loop()
{
 if (bt_iletisim.available())
 {
   char data = bt_iletisim.read();
   //Serial.println(data);
   if (data == '1') 
   {
     dur();
     delay(10); 
     ileri(); 
     son_islem = 1;
   }
   else if (data == '2')
   {
     dur();
     delay(10);
     geri(); 
     son_islem = 2;
   }
   else if (data == '3')
   {
     dur();
     delay(10);
     sol();
     son_islem = 3;
   }
   else if (data == '4')
   {
     dur();
     delay(10);
     sag();
     son_islem = 4;
   }
   else if (data == '6')
   {
     dur();
   }
   else if (data == '0')
   {
     motorlar_hiz = motorlar_hiz + 25;
     if (motorlar_hiz > 255)
     {
       motorlar_hiz = 255;
     }
     //Serial.print("motorlar hiz= ");
     //Serial.println(motorlar_hiz);
     son_isleme_devam_et();
   }
   else if (data == '5')
   {
     motorlar_hiz = motorlar_hiz - 25; 
     if (motorlar_hiz < 0) 
     {
       motorlar_hiz = 0;
     }
     //Serial.print("motorlar hiz= ");
     //Serial.println(motorlar_hiz);
     son_isleme_devam_et();
   }
   else if (data == '100') 
   {
     sicaklik_durum = false;
     nem_durum = false;
     gaz_durum = false;
   }
   else if (data == '101') 
   {
     sicaklik_durum = true;
     nem_durum = false;
     gaz_durum = false;
   }
   else if (data == '102') 
   {
     sicaklik_durum = false;
     nem_durum = true;
     gaz_durum = false;
   }
   else if (data == '103') 
   {
     sicaklik_durum = false;
     nem_durum = false;
     gaz_durum = true;
   }
 }
}
void ileri()
{
  digitalWrite(sol_ileri, 1);
  digitalWrite(sag_ileri, 1);
  digitalWrite(sol_geri, 0);
  digitalWrite(sag_geri, 0);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void geri()
{
  digitalWrite(sol_ileri, 0);
  digitalWrite(sag_ileri, 0);
  digitalWrite(sol_geri, 1);
  digitalWrite(sag_geri, 1);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void sol()
{
  digitalWrite(sol_ileri, 1);
  digitalWrite(sag_ileri, 0);
  digitalWrite(sol_geri, 0);
  digitalWrite(sag_geri, 0);
  analogWrite(sol_hiz, motorlar_hiz);
  analogWrite(sag_hiz, motorlar_hiz);
}
void sag()
{
  digitalWrite(sol_ileri,0);
  digitalWrite(sag_ileri, 1);
  digitalWrite(sol_geri, 0);
  digitalWrite(sag_geri, 0);
  analogWrite(sol_hiz, motorlar_hiz); 
  analogWrite(sag_hiz, motorlar_hiz);
}
void dur()
{
  digitalWrite(sol_ileri, 0);
  digitalWrite(sag_ileri, 0);
  digitalWrite(sol_geri, 0);
  digitalWrite(sag_geri, 0);
  analogWrite(sol_hiz, 0);
  analogWrite(sag_hiz, 0);
}
void son_isleme_devam_et()
{
  if (son_islem == 1)
  {
    ileri();
  }
  else if (son_islem == 2)
  {
    geri();
  }
  else if (son_islem == 3)
  {
    sol();
  }
  else if (son_islem == 4)
  {
    sag();
  }
}

void sicaklik_nem_gaz()
{
  int chk = DHT11.read(DHT11PIN); 
  
  if(sicaklik_durum)
  {
    //Serial.print("Sicaklik (Celcius): ");
    bt_iletisim.println((float)DHT11.temperature, 2);
  }
  else if(nem_durum)
  {
    //Serial.print("Nem (%): ");
    bt_iletisim.println((float)DHT11.humidity, 2);
  }
  else if(gaz_durum)
  {
    gaz_deger = analogRead(gaz_pin);
    bt_iletisim.println(gaz_deger);
  }
}
