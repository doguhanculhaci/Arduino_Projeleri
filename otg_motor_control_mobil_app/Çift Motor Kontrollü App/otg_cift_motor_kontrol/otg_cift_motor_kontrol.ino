#include <Servo.h> 

Servo fircasizMotor_bir;
Servo fircasizMotor_iki;

float MotorHIZI1 = 0, MotorHIZI2 = 0, gelen_veri = 0;

bool kullanici_kapatti = true, m1_degeri_geldi = false, m2_degeri_geldi = false;

void setup(){
  Serial.begin(9600);
  Serial.println("KURULUM YAPILIYOR.");
  
  fircasizMotor_bir.attach(3);
  fircasizMotor_iki.attach(5);
  
  Serial.println("KURULUM YAPILDI.");
}

void loop(){

  if(!kullanici_kapatti)
  {
    Serial.println("------AÇIK------");
    Serial.print("HIZ M1= ");
    Serial.println(MotorHIZI1);
    Serial.print("HIZ M2= ");
    Serial.println(MotorHIZI2);
    
    fircasizMotor_bir.write(MotorHIZI1);
    fircasizMotor_iki.write(MotorHIZI2);

    delay(15);
  }
  else if(kullanici_kapatti)
  {
    Serial.println("------KAPALI------");
    fircasizMotor_bir.write(0);
    fircasizMotor_iki.write(0);
  }
  
  veri_alma();

  delay(1000);
  
}

void veri_alma()
{
  while (Serial.available()>1) 
  {
    delay(15);
    gelen_veri = Serial.parseFloat();
    Serial.print("Gelen Veri= ");
    Serial.println(gelen_veri);
    
    if (gelen_veri == 200.00)     
    {
      Serial.println("SİSTEM AKTİF HALE GETİRİLDİ");
      MotorHIZI1 = 0;
      MotorHIZI2 = 0;
      kullanici_kapatti = false;
    }
    else if (gelen_veri == 300.00)     
    {
      Serial.println("SİSTEM PASİF HALE GETİRİLDİ");
      MotorHIZI1 = 0;
      MotorHIZI2 = 0;
      kullanici_kapatti = true;
    }
    else if(m1_degeri_geldi)
    {
      m1_degeri_geldi = false;
      MotorHIZI1 = gelen_veri;
    }
    else if(m2_degeri_geldi)
    {
      m2_degeri_geldi = false;
      MotorHIZI2 = gelen_veri;
    }
    else if(gelen_veri == 555.00 && !m1_degeri_geldi)
    {
      m1_degeri_geldi = true;
    }
    else if(gelen_veri == 666.00 && !m2_degeri_geldi)
    {
      m2_degeri_geldi = true;
    }
  } 
}
