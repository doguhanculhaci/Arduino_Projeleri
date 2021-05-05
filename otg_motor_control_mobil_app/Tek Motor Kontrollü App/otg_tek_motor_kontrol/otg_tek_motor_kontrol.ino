#include <Servo.h> 

Servo fircasizMotor_bir;
Servo fircasizMotor_iki;

float MotorHIZI = 0;

bool kullanici_kapatti = true;

void setup(){
  Serial.begin(9600);
  
  fircasizMotor_bir.attach(3);
  fircasizMotor_iki.attach(5);

  fircasizMotor_bir.writeMicroseconds(1000);
  fircasizMotor_iki.writeMicroseconds(1000);
}

void loop(){

  if(!kullanici_kapatti)
  {
    fircasizMotor_bir.write(MotorHIZI);
    fircasizMotor_iki.write(MotorHIZI);

    fircasizMotor_bir.writeMicroseconds(MotorHIZI); 
    fircasizMotor_iki.writeMicroseconds(MotorHIZI);
    delay(15);
  }
  else if(kullanici_kapatti)
  {
    fircasizMotor_bir.write(0);
    fircasizMotor_iki.write(0);
  }
  
  veri_alma();
  
}

void veri_alma()
{
  while (Serial.available()>1) 
  {
    delay(15);
    MotorHIZI = Serial.parseFloat();
    if (MotorHIZI == 200.00)     
    {
      MotorHIZI = 0;
      kullanici_kapatti = false;
    }
    else if (MotorHIZI == 300.00)     
    {
      MotorHIZI = 0;
      kullanici_kapatti = true;
    }
  } 
}
