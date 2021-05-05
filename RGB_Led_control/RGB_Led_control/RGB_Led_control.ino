int kirmizi = 3;  //Kırmızı led pin atamamızı gerçekleştirdik.
int yesil = 5;  //yesil led pin atamamızı gerçekleştirdik.
int mavi = 6; //mavi led pin atamamızı gerçekleştirdik.

int button_up = 7, button_down = 8; //Button pin atamamızı gerçekleştirdik.
int button_up_durum = 0, button_down_durum = 0; //Buton durumlarımızı sakladık.

int sw_bir = 9,sw_iki = 10,sw_uc = 11; //Anahtarlar için pin atamamızı gerçekleştirdik.

int sw_bir_durum = 0,sw_iki_durum = 0,sw_uc_durum = 0;//Anahtar durumlarımızı sakladık.

int kDeger,yDeger,mDeger; //Ledlerin parlaklık değerlerini sakladık.

int step = 5,parlaklik = 125; //Step ve parlaklık değeri başlangıç olarak belirlendi.

bool arttirildi_mi = false, azaltildi_mi = false; //Kontrol için bool değişkenleri atandı.

void setup()
{
  pinMode(kirmizi, OUTPUT);// Kırmızı led çıkış olarak atandı.   
  pinMode(yesil, OUTPUT);// Yesil led çıkış olarak atandı.
  pinMode(mavi, OUTPUT);// Mavi led çıkış olarak atandı.
  
  pinMode(button_up,INPUT); // Button giriş olarak atandı.
  pinMode(button_down,INPUT); // Button giriş olarak atandı.
  
  pinMode(sw_bir,INPUT);// Anahtar giriş olarak atandı.
  pinMode(sw_iki,INPUT);// Anahtar giriş olarak atandı.
  pinMode(sw_uc,INPUT);// Anahtar giriş olarak atandı.
}

void loop()
{
  sw_bir_durum = digitalRead(sw_bir);// Anahtar durumu kontrol edildi.
  sw_iki_durum = digitalRead(sw_iki);// Anahtar durumu kontrol edildi.
  sw_uc_durum = digitalRead(sw_uc);// Anahtar durumu kontrol edildi.
  
  button_up_durum = digitalRead(button_up);// Button durumu kontrol edildi.
  button_down_durum = digitalRead(button_down);// Button durumu kontrol edildi.
  
  //Sorud istenilen step kuralı gerçekleştirildi.
  if(button_up_durum && parlaklik < 255 && !arttirildi_mi)
  {
    parlaklik = parlaklik + step;
    arttirildi_mi = true;
  }
  else if(!button_up_durum && arttirildi_mi)
  {
    arttirildi_mi = false;
  }
  
  if(button_down_durum && parlaklik > 0 && !azaltildi_mi)
  {
    parlaklik = parlaklik - step;
    azaltildi_mi = true;
  }
  else if(!button_down_durum && azaltildi_mi)
  {
    azaltildi_mi = false;
  }
  
  // Soruda verilen şart gerçekleştirildi.
  if (sw_bir_durum && !sw_iki_durum && !sw_uc_durum)  
  {   
    //Parlaklık değerlerimiz değiştirildi.
    kDeger = parlaklik;  
    yDeger = 0;        
    mDeger = 0;            
  }
  // Soruda verilen şart gerçekleştirildi.
  else if (!sw_bir_durum && sw_iki_durum && !sw_uc_durum) 
  {
    //Parlaklık değerlerimiz değiştirildi.
    kDeger = 0;           
    yDeger = parlaklik;
    mDeger = 0;       
  }
  // Soruda verilen şart gerçekleştirildi.
  else if(!sw_bir_durum && !sw_iki_durum && sw_uc_durum)
  {
    //Parlaklık değerlerimiz değiştirildi.
    kDeger = 0;    
    yDeger = 0;           
    mDeger= parlaklik; 
  }
  // Soruda verilen şartların olmadığı durumlar için tüm ledler kapatıldı.
  else
  {
    //Parlaklık değerlerimiz değiştirildi.
    kDeger = parlaklik;    
    yDeger = parlaklik;           
    mDeger= parlaklik; 
  }

//RGB ledimize değerleri gönderiyoruz
  analogWrite(kirmizi, kDeger);  
  analogWrite(yesil, yDeger); 
  analogWrite(mavi, mDeger);  
}
