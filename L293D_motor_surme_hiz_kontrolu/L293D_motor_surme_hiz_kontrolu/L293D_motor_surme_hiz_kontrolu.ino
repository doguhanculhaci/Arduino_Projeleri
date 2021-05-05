#include <LiquidCrystal.h>; //Arduino LCD eklentisini çağırıyoruz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int ileriButton = 9; 
int geriButton = 10;  
int stopButton = 13;

int powerPin = 6;  
int input1 = 7;    
int input2 = 8;   

int hiz = 0;

boolean ileri = false, geri = false, dur = true; 

void setup (){
  Serial.begin(9600);
  
  pinMode (ileriButton, INPUT);
  pinMode (geriButton, INPUT);
  pinMode (powerPin, OUTPUT);
  pinMode (input1, OUTPUT);
  pinMode (input2, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); 
  lcd.print("Mert");
  lcd.setCursor(0, 1);                                   
  lcd.print("Cinar"); 
  
  delay(3000);
  
  lcd.setCursor(0, 0); 
  lcd.print("Ogrenci Numarasi");
  lcd.setCursor(0, 1);                                   
  lcd.print("190118020");
  
  delay(3000);
  
  lcd.clear();
}

void loop (){
  
  int stopDurum = digitalRead(stopButton);
  
  if(stopDurum)
  {
    dur = true;
    ileri = false;
    geri = false;
  }
  
  int ileriDurum = digitalRead(ileriButton);
  
  if (ileriDurum == 1)
  {
    dur = false;
    ileri = true;
    geri = false;
  }
  
  int geriDurum = digitalRead(geriButton);
  
  if (geriDurum == 1)
  {
    dur = false;
    ileri = false;
    geri = true;
  }
  
  if (ileri)
  {
    digitalWrite (input1, ileri);
    digitalWrite (input2, !ileri);  

    hiz = map (analogRead(A0),0,1023,0,100);  
    
    analogWrite(powerPin,hiz);
    
    lcd.setCursor(0, 0);                                   
    lcd.print("M. ileri donuyor");
    
    lcd.setCursor(0, 1);                                   
    lcd.print("Motor Hizi:%");
    lcd.print(hiz);
    lcd.print("    ");
  }
  else if(dur)
  { 
    digitalWrite (input1, ileri);
    digitalWrite (input2, !ileri);  
    
    analogWrite(powerPin,0);
    
    lcd.setCursor(0, 0);                                   
    lcd.print("Motor Durdu      ");
    lcd.setCursor(0, 1);                                   
    lcd.print("Motor Hizi:%0   ");
  }
  else if(geri)
  {
    digitalWrite (input1, ileri);
    digitalWrite (input2, !ileri);  

    hiz = map (analogRead(A0),0,1023,0,100);  
    
    analogWrite(powerPin,hiz);
    
    lcd.setCursor(0, 0);                                   
    lcd.print("M. geri donuyor ");
    
    lcd.setCursor(0, 1);                                   
    lcd.print("Motor Hizi:%");
    lcd.print(hiz);
    lcd.print("    ");
  }
  
}
