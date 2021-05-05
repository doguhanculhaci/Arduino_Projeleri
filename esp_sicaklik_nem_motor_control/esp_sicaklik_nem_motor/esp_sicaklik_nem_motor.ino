#include <SoftwareSerial.h>                             
#include <dht11.h>  

String agAdi = "TurkNet";                   //Ağımızın adını buraya yazıyoruz.    
String agSifresi = "Htc.Erhn.Arf.Mhmt!33";             //Ağımızın şifresini buraya yazıyoruz.

int rxPin = 10;                                               
int txPin = 11;                                               
int dht11Pin = 2;

int fan = 7;

float sicaklik, nem;

bool fan_calisiyor_mu = false;

int motorPin1 = 3, motorPin2 = 4, motorPin3 = 5, motorPin4 = 6; //Step motor pinlerini tanımlıyoruz.

dht11 DHT11;

SoftwareSerial esp(rxPin, txPin); 
  
void setup(){ 
  pinMode(fan,OUTPUT);                                          //FAN PİNİ ÇIKIŞ OLARAK ATANDI.
  
  digitalWrite(fan, HIGH);                                      //FAN ROLE İLE DEVRE DIŞI BIRAKILDI
  
  pinMode(motorPin1, OUTPUT);                                   //Motor pinleri OUTPUT olarak ayarlanır.
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  Serial.begin(9600);                                         //Seri haberleşmeyi başlatıyoruz.
  esp.begin(115200);    
  
  Serial.println("BAŞLIYOR 1");
  
  esp.println("AT");                                         //AT komutu ile modül kontrolünü yapıyoruz.
  while(!esp.find("OK")){                                    //Modül hazır olana kadar bekliyoruz.
    esp.println("AT");
  }
  delay(1000);  

  Serial.println("BAŞLIYOR 2"); 
  
  esp.println("AT+RST");                                     //ESP8266'yı resetliyoruz.
  delay(1000);
  while(!esp.find("ready"))                                  //Resetleme işleminin bitmesini bekliyoruz.
  {
    esp.println("AT+RST");
  }
  delay(1000);

  Serial.println("BAŞLIYOR 3"); 
  
  esp.println("AT+CWMODE=1");                               //Modülümüzü client olarak ayarlıyoruz.
  while(!esp.find("OK"))                                    //Ayarlamanın tamamlanmasını bekliyoruz.
  {
    esp.println("AT+CWMODE=1");  
  }

  Serial.println("BAŞLIYOR 4"); 
  
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");   //Wifi'a bağlanıyoruz.
  while(!esp.find("OK"))                                    //Bağlanana kadar bekliyoruz.
  {
    esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");
  }

  Serial.println("BAŞLIYOR 5"); 
  
  esp.print("AT+CIFSR\r\n");                                 //IP adresini ve MAC adresini okuyoruz.
  Serial.print(espOkuma(1000));                                 //IP ve MAC adresini ekrana yazıyoruz.
  serialTemizle(2000);                                          //Seri haberleşmede kullanmadığımız verileri temizliyoruz.
  esp.print("AT+CIPMUX=1\r\n");                              //Çoklu bağlantı ayarını yapıyoruz.
  serialTemizle(2000);
  esp.print("AT+CIPSERVER=1,80\r\n");                        //Server oluşturuyoruz ve 80. porttan dinlemeye başlıyoruz.
  serialTemizle(2000);

  Serial.println("BAŞLIYOR 6"); 
  
}
void loop(){

  //SICAKLIK VE NEM VERİLERİ OKUNUP KAYDEDİLDİ.
  DHT11.read(dht11Pin);
  
  sicaklik = (float)DHT11.temperature;
  nem = (float)DHT11.humidity;
  
  if(esp.available() > 0){                                       //Seri haberleşme verisi geldiğinde içindeki komutlar çalışır.
    if(esp.find("+IPD,")){                                   //Bağlantı isteği geldiğinde içindeki komutlar çalışır.
      delay(200);
      int connectionId = esp.read() - 48;                    //Bağlantı numarasını okuyoruz.
      String komut = espOkuma(1000);                         //Bağlantı komutlarını alıyoruz.    

      Serial.println("ŞUANDA ÇALIŞIYORUM"); 

      //DÖNDÜR BUTONUNA BASILINCA SİTE ADRESİNDE OLUŞAN BİLGİ İLE MOTOR DÖNDÜRME İŞLEMİ YAPILDI.  
      if(komut.indexOf("step=")){                    

        int baslangic_bir=komut.indexOf('=');
        String veri=komut.substring(baslangic_bir+1,baslangic_bir+4);

        int derece = veri.toInt();

        Serial.print("DERECE = "); 
        Serial.println(derece);
        
        if(derece >= 0)
        {
          for(int adim = 0; adim < derece; adim++)
          {                    
            stepIleri(50); 
          }
        }
        else if(derece < 0)
        {
          for(int adim = 0; adim > derece; adim--)
          {                    
            stepGeri(50); 
          }
        }
        
      }

      //FAN BUTONUNA BASILINCA SİTE ADRESİNDE OLUŞAN BİLGİ İLE FAN DEVREYE SOKULDU.

      if(komut.indexOf("step=fan") != -1){                    

        if(!fan_calisiyor_mu)
        {
          digitalWrite(fan, LOW);
          fan_calisiyor_mu = true;
        }
        else if(fan_calisiyor_mu)
        {
          digitalWrite(fan, HIGH);
          fan_calisiyor_mu = false;
        }

        Serial.print("FAN AKTİF Mİ = "); 
        Serial.println(fan_calisiyor_mu); 
        
      }


      //BU KISIMDA HTML KODLAR İLE SAYFA KURULUMU YAPILIYOR.

      String sayfa = "<h1>Sicaklik,Nem Okuma ve Step Motor Kontrol</h1>";
      sayfa+="<h3>Sicaklik Degeri = "+String(sicaklik)+" </h3>";  //SENSÖRDEN ALDIĞIMIZ SICAKLIK  VERİSİ YERİNE YAZILIDI.
      sayfa+="<h3>Nem Degeri = "+String(nem)+" </h3>";  //SENSÖRDEN ALDIĞIMIZ NEM  VERİSİ YERİNE YAZILIDI.
      sayfa+="<form method=get> Derece <input type='number' name=step value='0' min=-360 max= 360> <br><br>";  //DERECEMİZ MİN 360 VE MAX 360 OLARAK SINIRLANDIRILDI.
      sayfa+="<input type=submit value=Dondur></form><br>";
      sayfa+="<a href=\"?step=fan\"><button><h3>Fani Calistir</h1></button></a>";
      komut = "AT+CIPSEND=";                                    //Sayfa verisinin uzunluğu komut değişkenine eşitlenir.
      komut += connectionId;
      komut += ",";
      komut +=sayfa.length();
      komut +="\r\n";
      esp.print(komut);                                      //Komut gönderilir.
      delay(1000);
      esp.print(sayfa);                                      //Sayfa verisi gönderilir.
      delay(1000);
      komut = "AT+CIPCLOSE=";                                   //Bağlantı sonlandırma komutu ayarlanır.    
      komut+=connectionId;
      komut+="\r\n";
      esp.print(komut);                                      //Bağlantı sonlandırma komutu gönderilir. 
    }
  }
}
String espOkuma(long int zamanAsimi){                           //ESP'den gelen dönütleri okur.
  long int baslangic = millis();  
  String gelen;
  while(millis() - baslangic < zamanAsimi){                   
    if(esp.available()>0){
        char c = esp.read(); 
        gelen += c;
    } 
  }
  gelen.replace("AT+","");
  return gelen;
}
void serialTemizle(long int zamanAsimi){                         //Seri haberleşmede kullanmadığımız byteları temizler.
  long int baslangic = millis();
  while(millis() - baslangic < zamanAsimi){
    if(esp.available()>0){
        esp.read(); 
    } 
  }
}

//BU KISIMDA MOTOR SAAT YÖNÜNDE DÖNDÜRÜLÜYOR. BUDA MOTOR PİNLERİNİN SIRASI İLE ÇALIŞTIRILIP MANYETİK ALAN YARATMASI İLE OLUYOR.
void stepIleri(int beklemeSuresi){                            
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(beklemeSuresi);
}

//BU KISIMDA MOTOR SAAT YÖNÜNÜN TERSİNDE DÖNDÜRÜLÜYOR. BUDA MOTOR PİNLERİNİN SIRASI TERS YÖNDE ÇALIŞTIRILIP MANYETİK ALAN YARATMASI İLE OLUYOR.
void stepGeri(int beklemeSuresi){                                
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(beklemeSuresi);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
}
