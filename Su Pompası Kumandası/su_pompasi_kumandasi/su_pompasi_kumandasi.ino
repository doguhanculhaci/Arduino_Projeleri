int s_seviye_button = 2;
int l_lambasi = 3, p_pompasi = 4, a_vanasi = 5;

// 1 VE 2 NOLU SATIR = GEREKLİ PİNLERİN TANIMLAMASINI YAPTIK.

bool su_seviyesi_yukseldi = false, sure_yakala = true; 

// 6 NOLU SATIR = GEREKLİ ŞARTLARI SAĞLAMAK İÇİN BOOL DEĞER ATADIK.

float suanki_sure = 0, ilk_sure = 0;

// 10 NOLU SATIR = DALGALANMAYI ÖNLEMEK İÇİN BUTUNO NE KADAR SÜREDİR
// BASILDIĞINI ANLAMAK İÇİN KULLANILACAK.

int durum = 0;

// 15 NOLU SATIR = SEVİYESİNİ TEMSİL ETMESİ İÇİN ATANAN BUTONUN
// DURUMUNU KONTROL ETMEK İÇİN EKLENDİ.

void setup()
{
  // BUTONUMUZ GİRİŞ VE LEDLERİMİZ ÇIKIŞ PİNİ OLARAK ATANDI.
  pinMode(s_seviye_button, INPUT);
  
  pinMode(l_lambasi, OUTPUT);
  pinMode(p_pompasi, OUTPUT);
  pinMode(a_vanasi, OUTPUT);
}

void loop()
{
  // SU SEVİYESİ KONTROLÜ BAŞLATILDI.
  su_seviyesi_kontrol();

}

void su_seviyesi_kontrol()
{
  durum = digitalRead(s_seviye_button); //BUTON DURUMU KONTROL EDİLDİ.
    
  if(durum == 1)//BUTON BASILI İSE SU SEVİYESİ YÜKSELMİŞTİR.
  {
    dalgalanma_kontrolu(); //DALGALANMA KONTROLÜ FONKSİYONU BAŞLATILDI.
  }
  else
  {
    digitalWrite(l_lambasi, HIGH);
    digitalWrite(p_pompasi, HIGH);
    digitalWrite(a_vanasi, LOW);
  }
}

void dalgalanma_kontrolu()
{
  while(true) //BUTON DURUMU KONTROLÜ İÇİN BİR DÖNGÜYE GİRİLDİ.
  {
    suanki_sure = millis(); //O AN Kİ SÜRE VERİSİ SAYISAL OLARAK NOT ALINDI.
    
    if(sure_yakala == true)
    {
      ilk_sure = suanki_sure; //BUTONA BASILAN İLK SÜRE KAYDEDİLDİ.
      sure_yakala = false;
    }
    else if(sure_yakala == false && suanki_sure-ilk_sure > 3000)
    {
      //3 SANİYE SONRADA HALA SU SEVİYESİ YÜKSEK İSE BU BİR DALGALANMA DEĞİLDİR.
      
      sure_yakala = true;
      
      durum = digitalRead(s_seviye_button); //BUTONU TEKRAR KONROL EDİYORUZ.
      if(durum == 1) //BUTONA BASILI İSE SU SEVİYESİ HALA YÜKSEKTİR VE BU BİR DALGALANMA DEĞİLDİR.
      {
        //SU SEVİYESİNİN YÜKSEK OLDUĞU DURUM İÇİN GEREKLİ İŞLEMLER YAPILIR.
        su_seviyesi_yukseldi = true;
        
        digitalWrite(l_lambasi, LOW);
        digitalWrite(p_pompasi, LOW);
        digitalWrite(a_vanasi, HIGH);
      }
      else if(durum == 0 && su_seviyesi_yukseldi == true)
      {
        //SU SEVİYESİNİN YÜKSEKKEN DÜŞÜŞE GEÇİŞ YAPTIĞI DURUM İÇİN GEREKLİ İŞLEMLER YAPILIR.
        
        su_seviyesi_yukseldi = false;
        
        digitalWrite(l_lambasi, HIGH);
        digitalWrite(a_vanasi, LOW);
        delay(10000);
        digitalWrite(p_pompasi, HIGH);
        
      }
      else if(su_seviyesi_yukseldi == false)
      {
        //SU SEVİYESİNİN İLK BAŞTAKİ DÜŞÜK OLMA DURUMUNDA BURADA Kİ İŞLEMLER YAPILIR.
        
        su_seviyesi_yukseldi = false;
        
        digitalWrite(l_lambasi, HIGH);
        digitalWrite(p_pompasi, HIGH);
        digitalWrite(a_vanasi, LOW);
      }
            
      break;
    }
  } 
}
