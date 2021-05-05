# goz_kirpma_sayici

## Devre Şeması

**ARDUİNO MİNİ İÇİN GEREKLİDİR.**

![image](https://user-images.githubusercontent.com/53540561/117132608-bbff0f80-adab-11eb-98e6-04887b46f9a7.png)
![image](https://user-images.githubusercontent.com/53540561/117132633-c6b9a480-adab-11eb-9cb4-19e7bf5a252e.png)

**ARDUİNO NANO VB. KULLANICILARI DİREK BURADAN BAŞLAYABİLİR.**
![image](https://user-images.githubusercontent.com/53540561/117132653-ce794900-adab-11eb-865b-8277f8e0003d.png)


## Açıklama

**KOD YÜKLENİŞİ**

Devre1.png deki gibi bağlantılar yapılmalıdır. Sanırım bu net bir şekilde gözüküyor.
Daha sonra arduino yazılımından doğru COM’un seçilip ve doğru arduino sürümü seçilmelidir.
İlk başta bir nano olanı seçip bir dene eğer kodları başarılı yüklemez ise arduino mini seçeneklerinden kodları yüklemeyi dene.

**DEVRE KURULUMU**

1-SWİTCH BAĞLANTISI

Switch’in en sağ veya en sol bacağı bu fark etmez. Arduinodan 5V aldığımız yere bağlıyoruz.
Bu seferde diğer tarafta ki bacağından bir kablo ile arduinonun gndsine bir bağlantı yapıyoruz. 
Yine aynı bacak ile D7 pinine bir bağlantı yapıyoruz.

2-LED BAĞLANTISI

Led’in “+” bacağından arduino’nun 5V pinine bir bağlantı yapıyoruz.
Led’in “-” bacağına bir direnç bağlıyoruz. Bu direnç 330ohm veya 220 ohm olabilir.
Direncin diğer bacağından da arduino’nun D9 pinine bir bağlantı yapıyoruz.
Direncin iki bacağının aynı yolda olmamasına dikkat edilmelidir.

3-KIZILÖTESİ BAĞLANTISI

GND pini arduino’nun GND pinine bağlanmalıdır.
VCC pini arduino’nun 5V pinine bağlanmalıdır.
Diğer kalan pin ise arduino’nun A0 nolu pinine bağlanmalıdır.

## Arduino Kodları
```
#define mesafe_sensoru 11
#define led_bir 12

int sayac;

bool goz_kirpti_mi = false;

void setup() {
  
  pinMode(led_bir, OUTPUT);
  pinMode(mesafe_sensoru, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  int mesafe = digitalRead(mesafe_sensoru);
  
  Serial.print("Sensör Değer: ");
  Serial.println(mesafe);
  
  delay(100);
  
  if (mesafe == 1 && !goz_kirpti_mi)
  {
    sayac = sayac + 1;
    Serial.print("Göz kırpma sayısı = ");
    Serial.println(sayac);
    digitalWrite(led_bir,HIGH);
    goz_kirpti_mi = true;
  }
  else if(mesafe == 0 && goz_kirpti_mi)
  {
     digitalWrite(led_bir,LOW);
     goz_kirpti_mi = false;
  }
}
```
