#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

//MOTOR SÜRÜCÜ PİN ATAMALARI
const int in1 = 11;
const int in2 = 10;

//BUTTON PİN ATAMALARI
int button_bir = 6;
int button_iki = 7;

//ANAHTAR PİN ATAMALARI
int anahtar_bir = 8;
int anahtar_iki = 9;

bool ilk_defa_start_mi = true;
void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

//İLK KURULUMDA MOTOR DURDURULDU.
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

}

void loop() {

  if(ilk_defa_start_mi) //SİSTEM İLK DEFA AÇILIYOR MU KONTROLÜ YAPILACAK
  {
    ilk_defa_start_mi = false;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AD SOYAD");
    lcd.setCursor(0, 1);
    lcd.print("OKUL NUMARASI");

    delay(2000);

    lcd.clear();
    lcd.home();
    lcd.print("Akilli Ev Sist.");
    lcd.setCursor(0, 0);
  }
  
  //BUTON DURUMLARI KONTROL EDİLECEK
  int button_bir_durum = digitalRead(button_bir);
  int button_iki_durum = digitalRead(button_iki);


  if(button_bir_durum)
  {
    //PERDE AÇILMAK ÜZERE HAREKETE GEÇİCEK
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    while(true)
    {
      //ANAHTAR DURUMU KONTROL EDİLECEK
      int anahtar_bir_durum = digitalRead(anahtar_bir);

      if(anahtar_bir_durum)
      {
        //PERDE TAM AÇILDI İSE MOTOR DURDURULACAK VE EKRANA YAZI YAZDIRILACAK.
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);

        lcd.setCursor(0, 1);
        lcd.print("Perde acildi");

        break;
    
      }
    }
    
  }
  else if(button_iki_durum)
  {
    //PERDE KAPANMAK ÜZERE HAREKETE GEÇİCEK
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    while(true)
    {
      //ANAHTAR DURUMU KONTROL EDİLECEK
      int anahtar_iki_durum = digitalRead(anahtar_iki);

      if(anahtar_iki_durum)
      {
        //PERDE TAM KAPANDI İSE MOTOR DURDURULACAK VE EKRANA YAZI YAZDIRILACAK.
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    
        lcd.setCursor(0, 1);
        lcd.print("Perde kapandi");

        break;
      }
    }
  }
 
}
