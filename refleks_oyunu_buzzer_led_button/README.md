# refleks_oyunu_buzzer_led_button

## Devre Şeması
![image](https://user-images.githubusercontent.com/53540561/117131348-01224200-adaa-11eb-8166-efa843f107e0.png)

## Açıklama
İki kişinin refleks hızını ve ses algılama performansını ölçmek için bir makina tasarlanacak. 
1.	Her kullanıcı için ayrı buton  ( butonA, butonB)
2.	Butona basıldığını gösteren her kullanıcı için birer led:  birinci kullanıcı için kırmızı, ikinci kullanıcı için yeşil led 
3.	Testi başlatmak için START buton
4.	Start butona basıldığında rastgele iki sayı  üretilecek ve ikisi de Seri Ekranda görüntülenecek
5.	Birinci üretilen sayı, sürebilgisi : Start butona basıldıktan ses üretilene kadar geçecek süre
6.	İkinci Üretilen sayı  frekans : insan kulağının duyma aralığında (20–20.000 Hz) ses üretilecek 
7.	Rastgele frekansta üretilen ses 2 saniye boyunca duyulacak
8.	Sesi duyan kullanıcılar önlerindeki butona basacaklar
9.	Sadece en önce butona basan kişi için  LED yanacak. Diğer kullanıcıya ait LED butona basılsa bile yanmayacak. 
10.	İlk Basan kullanıcı için A veya B harflerinden biri Seri Ekranda yazdırılacak ( ilk basan birinci kullanıcı ise A, ikinci kullanıcı ise B)
11.	Test butonuna basıp yeni test başlatılana kadar LED yanık kalacak.


## Arduino Kodları
```
//BUTON DİGİTAL PİNLERİNİN TANIMLAMASI YAPILDI.
int start_button = 2;
int a_button = 3;
int b_button = 4;
int test_button = 5;

//LED DİGİTAL PİNLERİNİN TANIMLAMASI YAPILDI.
int a_led = 8;
int b_led = 9;

//SES İÇİN DİGİTAL PİN TANIMLAMASI YAPILDI.
int ses = 11;

//START BUTON VE OYUN RESET BUTONU DURUMLARI KAYIT EDİLMESİ İÇİN
// VERİ SAKLAMAK İÇİN DURUMLAR ADINDA 2 DEĞİŞKEN OLUŞTURULDU.
int start_durum = 0, test_durum = 0;
int a_button_degeri = 0, b_button_degeri = 0;


//SÜRE VE FREKANS VERİLERİ İNTEGER TÜRÜNDEN OLUŞTURULDU.
int surebilgisi;
int frekans;


//START VE RESET DURUMLARI İÇİN KULLANILACAK OLAN TRUE-FALSE EKLENDİ.
bool start_aktif_mi = false, test_aktif_mi = true;

void setup()
{
  Serial.begin(9600);  //SERİAL İLETİŞİM BAŞLATILDI.
  
  //BUTONLARIN GİRİŞ OLDUGU BELİRTİLDİ.
  pinMode(start_button, INPUT);
  pinMode(a_button, INPUT);
  pinMode(b_button, INPUT);
  pinMode(test_button, INPUT);
  
  //LEDLERİN ÇIKIŞ OLDUGU BELİRTİLDİ.
  pinMode(a_led, OUTPUT);
  pinMode(b_led, OUTPUT);
  
  //SESİN ÇIKIŞ OLDUGU BELİRTİLDİ.
  pinMode(ses, OUTPUT);
}

void loop()
{
  //BUTONLARA BASILIP BASILMADIĞI KONTROL EDİLDİ.
  start_durum = digitalRead(start_button);
  test_durum = digitalRead(test_button);
  
  //BUTONA BASILINCA STARTA TRUE DEĞERİ ATANDI.
  if(start_durum)
  {
    start_aktif_mi = true;
  }
  
  //BUTONA BASILINCA TESTE TRUE DEĞERİ ATANDI VE LEDLER KAPATILDI.
  if(test_durum)
  {
    test_aktif_mi = true;
    
    digitalWrite(a_led, LOW);
    digitalWrite(b_led, LOW);
  }
  
  //BUTONLARIN DURUMLARI KONTROL EDİLDİ.
  if(start_aktif_mi && test_aktif_mi)
  {
    surebilgisi = random(5000,10000); //Süre bilgisi rasgele olarak atandı.
    frekans = random(20,20000); //Frekans rasgele olarak atandı.
    
    //İstenilen bilgiler serial ekrana yazdırıldı.
    Serial.print("Sure Bilgisi = ");
    Serial.println(surebilgisi);
    
    Serial.print("Frekans = ");
    Serial.println(frekans);
    
    delay(surebilgisi); //Belirlenen süre kadar sistem yavaşlatıldı.
    
    tone(ses,frekans,500);//İstenilen frekansta 2 saniye ses üretildi.
    
    while(true)
    {
      //A VE B BUTONLARIN DURUMLARI SÜREKLİ OLARAK KONTROL EDİLDİ.
      a_button_degeri = digitalRead(a_button);
      b_button_degeri = digitalRead(b_button);
      
      //EGER A BUTONUNA ERKEN BASILIRSA BURADAKİ İŞLEMLER YAPILACAK.
      if(a_button_degeri)
      {
        digitalWrite(a_led, HIGH); //KIRMIZI LED YANDI.
        digitalWrite(b_led, LOW); //YEŞİL LED KAPALI TUTULDU.
        
        Serial.println("KAZANAN = A");//KAZANANIN İSMİ SERİAL EKRANA YAZILDI.
        
        test_aktif_mi = false;
        
        break; //WHİLE DÖNGÜSÜNDEN ÇIKILDI.
        
      }
      
      //EGER B BUTONUNA ERKEN BASILIRSA BURADAKİ İŞLEMLER YAPILACAK.
      if(b_button_degeri)
      {
        digitalWrite(a_led, LOW);//KIRMIZI LED KAPALI TUTULDU.
        digitalWrite(b_led, HIGH);//YEŞİL LED YANDI.
        
        Serial.println("KAZANAN = B");//KAZANANIN İSMİ SERİAL EKRANA YAZILDI.
        
        test_aktif_mi = false;
        
        break; //WHİLE DÖNGÜSÜNDEN ÇIKILDI.
      }
    }
  }
}
```
