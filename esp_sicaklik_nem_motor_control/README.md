# esp_sicaklik_nem_motor_control

## Devre Şeması

**DHT11 VE ESP BAĞLANTISI**

![image](https://user-images.githubusercontent.com/53540561/117128959-c36fea00-ada6-11eb-9220-906bf24c6ad7.png)

**MOTOR SÜRÜCÜ VE SERVO BAĞLANTISI**

Kırmızı ile boyalı olan sensörün bağlantıları dikkate alınmamalıdır.

![image](https://user-images.githubusercontent.com/53540561/117128992-cc60bb80-ada6-11eb-8f19-dc2ab0b5c7b5.png)


## Açıklama
DAHA SONRA EKLENECEKTİR


## Arduino Kodları
###### Klasörün içerisinde bir kaç kod daha vardır olmaz ise onları deneyebilirsiniz.
```
#include <SoftwareSerial.h>                             
#include <dht11.h>  

String agAdi = "dogu";                   //Ağımızın adını buraya yazıyoruz.    
String agSifresi = "123123123";             //Ağımızın şifresini buraya yazıyoruz.

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
  pinMode(fan,OUTPUT);
  
  digitalWrite(fan, HIGH);
  
  pinMode(motorPin1, OUTPUT);                                   //Motor pinleri OUTPUT olarak ayarlanır.
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  Serial.begin(9600);                                         //Seri haberleşmeyi başlatıyoruz.
  esp.begin(115200);    
  
  esp.println("AT");                                         //AT komutu ile modül kontrolünü yapıyoruz.
  while(!esp.find("OK")){                                    //Modül hazır olana kadar bekliyoruz.
    esp.println("AT");
  }
  delay(1000);  
  esp.println("AT+RST");                                     //ESP8266'yı resetliyoruz.
  delay(1000);
  while(!esp.find("ready"))                                  //Resetleme işleminin bitmesini bekliyoruz.
  delay(1000);
  esp.println("AT+CWMODE=1");                                //Modülümüzü client olarak ayarlıyoruz.
  while(!esp.find("OK"));                                    //Ayarlamanın tamamlanmasını bekliyoruz.
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");   //Wifi'a bağlanıyoruz.
  while(!esp.find("OK"));                                    //Bağlanana kadar bekliyoruz.
  esp.print("AT+CIFSR\r\n");                                 //IP adresini ve MAC adresini okuyoruz.
  Serial.print(espOkuma(1000));                                 //IP ve MAC adresini ekrana yazıyoruz.
  serialTemizle(2000);                                          //Seri haberleşmede kullanmadığımız verileri temizliyoruz.
  esp.print("AT+CIPMUX=1\r\n");                              //Çoklu bağlantı ayarını yapıyoruz.
  serialTemizle(2000);
  esp.print("AT+CIPSERVER=1,80\r\n");                        //Server oluşturuyoruz ve 80. porttan dinlemeye başlıyoruz.
  serialTemizle(2000);
}
void loop(){

  DHT11.read(dht11Pin);
  
  sicaklik = (float)DHT11.temperature;
  nem = (float)DHT11.humidity;
  
  if(esp.available()){                                       //Seri haberleşme verisi geldiğinde içindeki komutlar çalışır.
    if(esp.find("+IPD,")){                                   //Bağlantı isteği geldiğinde içindeki komutlar çalışır.
      delay(200);
      int connectionId = esp.read() - 48;                    //Bağlantı numarasını okuyoruz.
      String komut = espOkuma(1000);                         //Bağlantı komutlarını alıyoruz.    
      
      if(komut.indexOf("=")){                    

        int baslangic=komut.indexOf('=');
        komut=komut.substring(baslangic+1,baslangic+4);

        int derece = komut.toInt();
        
        if(derece >= 0)
        {
          for(int adim = 0; adim < derece; adim++)
          {                    
            stepIleri(50); 
          }
        }
        else if(derece < 0)
        {
          for(int adim = 0; adim > derece; adim++)
          {                    
            stepGeri(50); 
          }
        }
        
      }

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
        
      }

      String sayfa = "<h1>Sıcaklık,Nem Okuma ve Step Motor Kontrol</h1>";
      sayfa+="<h3>Sicaklik Degeri = "+String(sicaklik)+" </h3>";
      sayfa+="<h3>Nem Degeri = "+String(nem)" </h3>";
      sayfa+="<form method=get> Derece <input type='number' name=step value='0' min=-360 max= 360> <br><br>";
      sayfa+="<input type=submit value=Dondur></form><br>";
      sayfa+="<a href=\"?step=fan\"><button><h3>Fani Calistirir</h1></button></a>";
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
```
