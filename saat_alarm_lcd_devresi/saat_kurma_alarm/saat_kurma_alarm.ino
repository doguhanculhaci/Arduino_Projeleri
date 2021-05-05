#include <SPI.h>
#include <SD.h>
#include <Keypad.h> 
#include <Wire.h>
#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>

File myFile;

LiquidCrystal_I2C lcd(0x27, 16, 2);

virtuabotixRTC myRTC(10, 11, 12);

///KEYPAD AYARLARI
const byte numRows= 4; 

const byte numCols= 3; 

char keymap[numRows][numCols]= 
{
{'1', '2', '3'}, 

{'4', '5', '6'}, 

{'7', '8', '9'},

{'*', '0', '#'}
};

byte rowPins[numRows] = {9,8,7,6}; 
byte colPins[numCols]= {5,4,3}; 

int i1,i2,i3,i4;
char c1,c2,c3,c4;
char keypressed,keypressedx;

int A_hour=NULL;
int A_minute=NULL;
int AlarmIsActive=NULL;

int buzzer = 2;

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
///

void setup() {

  Serial.begin(9600);

  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
 
  lcd.begin (); 

/*
  Serial.println("SD Kart başlatılıyor...");

  if(!SD.begin())
  {
    Serial.println("Başlatma başarısız oldu.");
    return;
  }
  Serial.println("Başlatma yapıldı.");

  */
}

void loop() {

  veri_yoksa();

  saat_ayari();

  alarm_ayari();

  alarm_sil();
}

void veri_yoksa(){

  while(keypressed == NO_KEY)
  {                            
    keypressed = myKeypad.getKey();
    lcd.clear(); 
    myRTC.updateTime();

    if(myRTC.hours==A_hour && myRTC.minutes==A_minute && AlarmIsActive==1 && myRTC.seconds >= 0 && myRTC.seconds <= 2)
    {
      while(keypressedx == NO_KEY)
      {
        tone(buzzer, 1000); 
        delay(100);
        tone(buzzer, 2000);
        delay(100);
        lcd.clear();
        lcd.print("     Alarm"); //Alarm çaldığında ekrana yazan yazı.(i,ü,ö,ğ,ş,küçük j,ç harflerini ve benzeri şeyleri kullanmayın.)
        keypressedx = myKeypad.getKey();
      }
    }
    keypressedx = NO_KEY;
    noTone(buzzer);
    
    lcd.setCursor(0,0);
    lcd.print(myRTC.dayofmonth);
    lcd.print("/");
    lcd.print(myRTC.month);
    lcd.print("/");
    lcd.print(myRTC.year);
    lcd.setCursor(0,1);
    lcd.print(myRTC.hours);
    lcd.print(":");
    lcd.print(myRTC.minutes);
    lcd.print(":");
    lcd.print(myRTC.seconds);
    delay(100);
  }
}

void saat_ayari(){
  if (keypressed == '*') //Ayarlar menüsü tuşu. 
  {
    lcd.clear();
    lcd.print("     Ayarlar");
    delay(1000);
    lcd.clear();
    lcd.print("Yil Ayari");

    char keypressed2 = myKeypad.waitForKey();  
    if (keypressed2 != NO_KEY && keypressed2 !='*' && keypressed2 !='#' && keypressed2 !='A' && keypressed2 !='B' && keypressed2 !='C' && keypressed2 !='D' )
    {
      c1 = keypressed2;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    char      keypressed3 = myKeypad.waitForKey();
    if (keypressed3 != NO_KEY && keypressed3 !='*' && keypressed3 !='#' && keypressed3 !='A' && keypressed3 !='B' && keypressed3 !='C' && keypressed3 !='D' )
    {
      c2 = keypressed3;
      lcd.setCursor(1, 1);
      lcd.print(c2);
    }
    char  keypressed4 = myKeypad.waitForKey();
    if (keypressed4 != NO_KEY && keypressed4 !='*' && keypressed4 !='#' && keypressed4 !='A' && keypressed4 !='B' && keypressed4 !='C' && keypressed4 !='D' )
    {
      c3 = keypressed4;
      lcd.setCursor(2, 1);
      lcd.print(c3);
    }
    char   keypressed5 = myKeypad.waitForKey();
    if (keypressed5 != NO_KEY && keypressed5 !='*' && keypressed5 !='#' && keypressed5 !='A' && keypressed5 !='B' && keypressed5 !='C' && keypressed5 !='D' )
    {
      c4 = keypressed5;
      lcd.setCursor(3, 1);
      lcd.print(c4);
    }

    i1=(c1-48)*1000;        
    i2=(c2-48)*100;
    i3=(c3-48)*10;
    i4=c4-48;
  
    int N_year=i1+i2+i3+i4;
    delay(500);
    lcd.clear();
    lcd.print("Ay Ayari");
////////////////////////////////////////////////////////////////

    char keypressed6 = myKeypad.waitForKey();  
    if (keypressed6 != NO_KEY && keypressed6 !='*' && keypressed6 !='#' && keypressed6 !='A' && keypressed6 !='B' && keypressed6 !='C' && keypressed6 !='D' )
    {
      c1 = keypressed6;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    char   keypressed7 = myKeypad.waitForKey();
    if (keypressed7 != NO_KEY && keypressed7 !='*' && keypressed7 !='#' && keypressed7 !='A' && keypressed7 !='B' && keypressed7 !='C' && keypressed7 !='D' )
    {
      c2 = keypressed7;
      lcd.setCursor(1, 1);
      lcd.print(c2);
    }

    i1=(c1-48)*10;
    i2=c2-48;
    int N_month=i1+i2;
    delay(500);

    lcd.clear();
    lcd.print("Gun Ayari");
////////////////////////////////////////////////////////////////  
                  
    char keypressed8 = myKeypad.waitForKey();  
    if (keypressed8 != NO_KEY && keypressed8 !='*' && keypressed8 !='#' && keypressed8 !='A' && keypressed8 !='B' && keypressed8 !='C' && keypressed8 !='D' )
    {
      c1 = keypressed8;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    char keypressed9 = myKeypad.waitForKey();
    if (keypressed9 != NO_KEY && keypressed9 !='*' && keypressed9 !='#' && keypressed9 !='A' && keypressed9 !='B' && keypressed9 !='C' && keypressed9 !='D' )
    {
      c2 = keypressed9;
      lcd.setCursor(1, 1);
      lcd.print(c2);
    }

    i1=(c1-48)*10;
    i2=c2-48;
    int N_day=i1+i2;
    delay(500);
    lcd.clear();
    lcd.print("Saat Ayari");
////////////////////////////////////////////////////////////////////////// 
                  
    char keypressed10 = myKeypad.waitForKey();  
    if (keypressed10 != NO_KEY && keypressed10 !='*' && keypressed10 !='#' && keypressed10 !='A' && keypressed10 !='B' && keypressed10 !='C' && keypressed10 !='D' )
    {
      c1 = keypressed10;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    char keypressed11 = myKeypad.waitForKey();
    if (keypressed11 != NO_KEY && keypressed11 !='*' && keypressed11 !='#' && keypressed11 !='A' && keypressed11 !='B' && keypressed11 !='C' && keypressed11 !='D' )
    {
      c2 = keypressed11;
      lcd.setCursor(1, 1);
      lcd.print(c2);
    }
    
    i1=(c1-48)*10;
    i2=c2-48;
    int N_hour=i1+i2;
    delay(500);
    lcd.clear();
    lcd.print("Dakika Ayari");
//////////////////////////////////////////////////////////////////////////////////

    char keypressed12 = myKeypad.waitForKey();  
    if (keypressed12 != NO_KEY && keypressed12 !='*' && keypressed12 !='#' && keypressed12 !='A' && keypressed12 !='B' && keypressed12 !='C' && keypressed12 !='D' )
    {
      c1 = keypressed12;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    char keypressed13 = myKeypad.waitForKey();
    if (keypressed13 != NO_KEY && keypressed13 !='*' && keypressed13 !='#' && keypressed13 !='A' && keypressed13 !='B' && keypressed13 !='C' && keypressed13 !='D' )
    {
    c2 = keypressed13;
    lcd.setCursor(1, 1);
    lcd.print(c2);
    }

    i1=(c1-48)*10;
    i2=c2-48;
    int N_minutes=i1+i2;
    delay(500);
    lcd.clear();

    myRTC.setDS1302Time(22, N_minutes, N_hour, 1, N_day, N_month, N_year);

    keypressed=NO_KEY; 
  }
}

void alarm_ayari(){
/////////////////////////////////////////Alarm Ayarı/////////////////////////////////
  if (keypressed == '#')
  {
    //myFile = SD.open("test.txt", FILE_WRITE);
    
    lcd.clear();
    lcd.print("  Alarm Ayari  ");
    delay(1000);
    lcd.clear();
    lcd.print("Alarm Saati");
    
    char keypressed14 = myKeypad.waitForKey(); 
    if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )
    {
      c1 = keypressed14;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    
    char keypressed15 = myKeypad.waitForKey();
    if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )
    {
      c2 = keypressed15;
      lcd.setCursor(1, 1);
      lcd.print(c2);
    }

    i1=(c1-48)*10;
    i2=c2-48;
    A_hour=i1+i2;
    delay(500);

    lcd.clear();
    lcd.print("Alarm Dakikasi");
    
    char keypressed16 = myKeypad.waitForKey(); 
    if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )
    {
      c1 = keypressed16;
      lcd.setCursor(0, 1);
      lcd.print(c1);
    }
    
    char keypressed17 = myKeypad.waitForKey();
    if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )
    {
      c2 = keypressed17;
      lcd.setCursor(1, 1);
      lcd.print(c2);
    }

    i1=(c1-48)*10;
    i2=c2-48;
    A_minute=i1+i2;
    delay(500);
 
    lcd.clear();
    AlarmIsActive=1;
    keypressed=NO_KEY;

/*  SD KARTA YAZMA KODLARI BURADA
    if(myFile)
    {
      Serial.println("test.txt dosyasına yazılıyor...");
      myFile.print("Alarım Bilgisi: ");
      myFile.print("Saat = ");
      myFile.print(A_hour);
      myFile.print(", Dakika = ");
      myFile.println(A_minute);
      myFile.close();
    }
    else
    {
      Serial.println("test.txt dosyası açılırken hata.");
    }
    */
  }
}

void alarm_sil()
{
  if (keypressed == '0')
  {
    lcd.clear();
    lcd.print("Alarm yok");
    AlarmIsActive=0;
    keypressed=NO_KEY;
    delay(500);
  }
  else 
  {
    myRTC.updateTime();
    keypressed=NO_KEY;
  }
}
