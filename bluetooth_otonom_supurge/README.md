# bluetooth_otonom_supurge

## Devre Şeması

DEVRE ŞEMASINI KAYBETMİŞİM FAKAT KODLARDA Kİ PİN ATAMALARINDAN YENİ BİR DEVRE ŞEMASI OLUŞTURABİLİRSİNİZ.

## Açıklama
Bluetooth ile sadece aç kapa işlemi yapılabilir.
1. BT MODUL HC05 
https://www.robotistan.com/hc05-bluetooth-serial-modul-karti-hc05-bluetooth-to-serial-port-module-br?gclid=CjwKCAjwhMmEBhBwEiwAXwFoEVxdsG_pJODFZUfCTL4TKLLZdTvPkgdil3UNsJ_0_zLgb4fxytRjYxoCcq8QAvD_BwE

2. ÇİFT KANAL DC MOTOR SÜRÜCÜ 1 ADET
https://www.direnc.net/l298-dc-step-motor-surucu?gclid=Cj0KCQiAifz-BRDjARIsAEElyGJihnU1noGAhgNHp9_8Dbj9eFFN3ve0A5SAoSsTO8A9r2t3O0e0_u4aAsT6EALw_wcB

3. SERVO MOTOR 1 ADET
https://www.direnc.net/sg90-9g-servo-motor?gclid=Cj0KCQiAifz-BRDjARIsAEElyGL6t5QIkzJ9MfvpyihOql7uxT4L8VYNGhq4M9aTDMkqHP7JESpKTsgaAhEUEALw_wcB

4. KIZILÖTESİ 3 ADET
https://www.robotzade.com/urun/ir20-kizilotesi-5v-sensor

5. ARDUİNO NANO 1 ADET
https://www.robotistan.com/arduino-nano

6. 2 ADET DC MOTOR 2 ADET TEKERLEK



## Arduino Kodları
```
#include <Servo.h>

Servo sg90;

const int on_sensor = 3, sag_sensor = 4 ,sol_sensor = 5;

const int DonmeHizi = 175;
/* bu değişken ile motorların dönme hızı kontrol edilebilir */
const int TamDonmeZamani = 1000;
const int CeyrekDonmeZamani = 250;
/* DonmeZamani değişkeni robotun 90 derece dönmesini sağlayan değişkendir
 * Robotun yaklaış 90 derece dönmesi için robotunuza göre bu süreyi ayarlayın 
 */ 

/* motor sürücüsüne bağlanacak INPUT ve ENABLE pinleri belirleniyor */
const int sagileri = 9;
const int saggeri = 8;
const int solileri = 12;
const int solgeri = 13;
const int solenable = 11;
const int sagenable = 10;

String readString;

bool aydinlik_mi = false, sistem_aktif = false;
int ortam_aydinligi = 0;

void setup() {
  
  Serial.begin(9600);
  
  sg90.attach(7);
  
  pinMode(on_sensor, INPUT);
  pinMode(sag_sensor, INPUT);
  pinMode(sol_sensor, INPUT);

   /* motorları kontrol eden pinler çıkış olarak ayarlanıyor */
  pinMode(sagileri,OUTPUT);
  pinMode(saggeri,OUTPUT);
  pinMode(solileri,OUTPUT);
  pinMode(solgeri,OUTPUT);
  pinMode(sagenable,OUTPUT);
  pinMode(solenable,OUTPUT);
  
}

void loop() {

  if(sistem_aktif && ortam_aydinligi > 800 )
  {
    sg90.write(120);

    while( digitalRead(on_sensor) == 1 && sistem_aktif && ortam_aydinligi > 800)
    { // önüne engel gelene kadar düz git
        ileri(DonmeHizi);
    }
    
    dur();

    if(!sistem_aktif || ortam_aydinligi < 800 )
    {
      goto kapat;
    }
  
    delay(500);
  
    int sag_deger = digitalRead(sag_sensor);
    int sol_deger = digitalRead(sol_sensor);
  
    if(sag_deger == 0)
    {
      sagaDon(DonmeHizi);
      delay(CeyrekDonmeZamani);
      dur();
    }
    else if(sol_deger == 0)
    {
      solaDon(DonmeHizi);
      delay(CeyrekDonmeZamani);
      dur();
    }
    else
    {
      sagaDon(DonmeHizi);
      delay(TamDonmeZamani);
      dur();
    }
    delay(500);
  }
  else if(!sistem_aktif && ortam_aydinligi > 800)
  {
    kapat:
    sg90.write(90);
    dur();
  }
  
}

void ileri(int hiz)
{
  veri_alma();
  ortam_aydinligi = analogRead(A0);
  /* ilk değişkenimiz sag motorun ikincisi sol motorun hızını göstermektedir.
   * motorlarımızın hızı 0-255 arasında olmalıdır.
   * Fakat bazı motorların torkunun yetersizliğiniden 60-255 arasında çalışmaktadır.
   * Eğer motorunuzdan tiz bir ses çıkıyorsa hızını arttırmanız gerekmektedir.
   */
  analogWrite(sagenable, hiz); /* sağ motorun hız verisi */
  digitalWrite(sagileri,HIGH); /* ileri dönme sağlanıyor */
  digitalWrite(saggeri,LOW); /* ileri dönme sağlanıyor */

  analogWrite(solenable, hiz); /* sol motorun hız verisi */
  digitalWrite(solileri, HIGH); /* ileri dönme sağlanıyor */
  digitalWrite(solgeri,LOW); /* ileri dönme sağlanıyor */
}

void sagaDon(int hiz)
{
  veri_alma();
  ortam_aydinligi = analogRead(A0);
  analogWrite(sagenable, hiz); /* sağ motorun hız verisi */
  digitalWrite(sagileri,LOW); /* geri dönme sağlanıyor */
  digitalWrite(saggeri,HIGH); /* geri dönme sağlanıyor */

  analogWrite(solenable, hiz); /* sol motorun hız verisi */
  digitalWrite(solileri, HIGH); /* ileri dönme sağlanıyor */
  digitalWrite(solgeri,LOW); /* ileri dönme sağlanıyor */
}

void solaDon(int hiz)
{
  veri_alma();
  ortam_aydinligi = analogRead(A0);
  analogWrite(sagenable, hiz); /* sağ motorun hız verisi */
  digitalWrite(sagileri,HIGH); /* ileri dönme sağlanıyor */
  digitalWrite(saggeri,LOW); /* ileri dönme sağlanıyor */

  analogWrite(solenable, hiz); /* sol motorun hız verisi */
  digitalWrite(solileri, LOW); /* geri dönme sağlanıyor */
  digitalWrite(solgeri,HIGH); /* geri dönme sağlanıyor */
}

void dur()
{
  veri_alma();
  ortam_aydinligi = analogRead(A0);
  /* Tüm motorlar kitlenerek durma sağlanıyor */
  digitalWrite(sagileri, HIGH);
  digitalWrite(saggeri, HIGH);
  digitalWrite(solileri, HIGH);
  digitalWrite(solgeri, HIGH);
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
    Serial.println(readString);
    
    if (readString == "ac")     
    {
      Serial.println("SUPURGE AKTİF HALE GETIRILDI. ");
      Serial.println("HADI SUPURELIM... ");
      sistem_aktif = true;
    }

    if (readString == "kapat")     
    {
      Serial.println("SUPURGE PASIF HALE GETIRILDI. ");
      sistem_aktif = false;
    }
    readString="";
  } 
}
```
