# yangin_alarmi_sicaklik_gaz_control

## Devre Şeması
![image](https://user-images.githubusercontent.com/53540561/117137095-e784f880-adb1-11eb-9a53-cbf862cf8b92.png)

## Açıklama
Gaz Sensörü,  ve Sıcaklık Sensöründen alınacak değerler seri Monitörde görüntülenecek. 

1.	Okunan sıcaklık değeri 40°C’den daha yüksek ve duman değeri orta seviye ( 450 – 600)  ise SARI LED yanacak ve piezodan 200 Hz kesikli ses duyulacak.
2.	Okunan sıcaklık değeri 50°C’den daha yüksek ve duman değeri yüksek seviye 600’den yüksek  ise KIRMIZI LED yakılacak  ve piezodan 500 Hz kesikli ses duyulacak.
3.	Sıcaklık değeri 40°C’den daha düşük ve duman sensörü değeri 450’nin altında ise YEŞİL LED yanacak. Ses duyulmayacak..



## Arduino Kodları
```
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
  sicaklik_degeri = ((deger*4.88) - 500 ) / 10	;// Sıcaklık değeri işlendi.
  
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
```
