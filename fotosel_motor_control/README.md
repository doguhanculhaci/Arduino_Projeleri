# fotosel_motor_control

## Devre Şeması
![image](https://user-images.githubusercontent.com/53540561/117132433-83f7cc80-adab-11eb-9102-5ff0a16ebd7f.png)

## Açıklama
DAHA SONRA EKLENECEKTİR.

## Arduino Kodları
```
#include <Servo.h>
#define pir 11
#define start_button 4
bool start = false;
Servo motor_B0;
Servo motor_B1;
Servo motor_M2;
Servo motor_M3;
Servo motor_M4;

int deger=0, buton_durum = 0, sayac = 0, sayac_artti = 0;

void setup() {
  motor_B0.attach(6);
  motor_B1.attach(7);
  motor_M2.attach(8);
  motor_M3.attach(9);
  motor_M4.attach(10);
  
  motor_B0.write(0);
  motor_B1.write(0);
  motor_M2.write(0);
  motor_M3.write(0);
  motor_M4.write(0);
  
  pinMode(pir,INPUT);
  pinMode(start_button,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  deger=digitalRead(pir);
  buton_durum = digitalRead(start_button);
    
  if(buton_durum && start == false)
  {
    start = true;
    Serial.println("SISTEM CALISMAYA BASLADI");
  }
  
  if(start)
  {
    motor_B0.write(90);
    motor_B1.write(90);
    
    if(deger == HIGH && sayac_artti == 0) 
    { 
      sayac = sayac + 1 ;
      sayac_artti = 1;
      Serial.println(sayac);
    }
    else if(deger == LOW && sayac_artti == 1)
    {
      sayac_artti = 0;
    }
    
    if(sayac == 2)
    {
     motor_M2.write(90);
    }
    else if(sayac == 4)
    {
     motor_M3.write(90);
    }
    else if(sayac == 6)
    {
     motor_M4.write(90);
    }   
    else if(sayac == 8)
    {
      sayac = 0;
      start = false;
      motor_M2.write(0);
      motor_M3.write(0);
      motor_M4.write(0);
    }  
  }    
}
```
