int buzzer = 3;  //Buzzer pin atamamızı gerçekleştirdik.
int sicaklik_pin = A0; //Sıcaklık sensörü pin atamamızı gerçekleştirdik.
int gaz_pin = A1; //Gaz sensörü pin atamamızı gerçekleştirdik.
int sicaklik_degeri,gaz_degeri; //Gaz değerlerini saklamak için gerekli değerler atandı.

#define ledKirmizi 4
#define ledSari 5
#define ledYesil 6

//Ledlerimiz için pin atamamızı gerçekleştirdik.

void setup()   
{
  
  Serial.begin(9600); //Seri monitör iletişimi başlatıldı.
  
  pinMode(buzzer, OUTPUT);// Buzzer çıkış olarak atandı.
  
  pinMode(ledKirmizi, OUTPUT);// Kırmızı led çıkış olarak atandı.
  pinMode(ledSari, OUTPUT);// Sarı led çıkış olarak atandı.
  pinMode(ledYesil, OUTPUT);// Yesil led çıkış olarak atandı.
  
}

void loop()   
{
  gaz_degeri = analogRead(gaz_pin); // Gaz değeri okundu.
  
  Serial.print("Gaz Degeri: ");
  Serial.println(gaz_degeri);// Gaz değeri ekrana yazdırıldı.
 
  int deger = analogRead(sicaklik_pin);// Sıcaklık değeri okundu.
  sicaklik_degeri = ((deger*4.88) - 500 ) / 10  ;// Sıcaklık değeri işlendi.
  
  Serial.print("Sicaklik Degeri: ");
  Serial.print(sicaklik_degeri);
  Serial.println(" C ");// Sıcaklık değeri ekrana yazdırıldı. 
  
  // Soruda verilen şart gerçekleştirildi.
  if (sicaklik_degeri > 40 && gaz_degeri<600 && gaz_degeri>450)
  {
    tone(buzzer,200);// Buzzer 200Hz ile çalıştırıldı.
    
    digitalWrite(ledKirmizi,LOW);// Kırmızı led kapatıldı.
    digitalWrite(ledSari,HIGH);// Sarı led açıldı.
    digitalWrite(ledYesil,LOW);// Yesli led kapatıldı.
  }
  // Soruda verilen şart gerçekleştirildi.
  else if(sicaklik_degeri > 50 && gaz_degeri>600)
  {
    tone(buzzer,500);// Buzzer 500Hz ile çalıştırıldı.
    
    digitalWrite(ledKirmizi,HIGH);// Kırmızı led açıldı.
    digitalWrite(ledSari,LOW);// Sarı led kapatıldı.
    digitalWrite(ledYesil,LOW);// Yesil led kapatıldı.
  }
  // Soruda verilen şart gerçekleştirildi.
  else if(sicaklik_degeri < 40 && gaz_degeri<450)
  {
    noTone(buzzer);// Buzzer kapatıldı.
    
    digitalWrite(ledKirmizi,LOW);// Kırmızı led kapatıldı.
    digitalWrite(ledSari,LOW);// Sarı led kapatıldı.
    digitalWrite(ledYesil,HIGH);// Yesil led açıldı.
  }  
}
