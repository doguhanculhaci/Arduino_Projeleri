#define sicaklik A0
#define basinc A1

int isitici = 2, soguksu_besleyici = 3, emniyet_valfi = 4, karistirici = 5;

int baslangic = 6, normal = 7, alarm = 8;

int basinc_degeri = 0, sicaklik_degeri = 0;

bool isitici_durumu = false, soguk_su_durumu = false;

void setup()
{
  Serial.begin(9600);
  
  pinMode(sicaklik, INPUT);
  pinMode(basinc, INPUT);
  
  pinMode(isitici, OUTPUT);
  pinMode(soguksu_besleyici, OUTPUT);
  pinMode(emniyet_valfi, OUTPUT);
  pinMode(karistirici, OUTPUT);
  pinMode(baslangic, OUTPUT);
  pinMode(normal, OUTPUT);
  pinMode(alarm, OUTPUT);
}

void loop()
{
  basinc_degeri = analogRead(basinc);
  sicaklik_degeri = analogRead(sicaklik);
  
  Serial.print("Sicaklik Degeri: ");
  Serial.println(sicaklik_degeri);
  Serial.print("Basinc Degeri: ");
  Serial.println(basinc_degeri);
  
  delay(500);
  
  Serial.println("----------DURUM RAPORU----------");
  isitici_kontrolu();
     
  soguk_su_beslemesi_kontrolu();
  
  emniyet_valfi_kontrolu();
  
  karistirici_kontrolu();
  
  genel_sistem_kontrol();
  
}

void isitici_kontrolu()
{
  if(sicaklik_degeri < 250 && (basinc_degeri < 250 || (sicaklik_degeri > 250 && sicaklik_degeri < 750)))
  {
    Serial.println("Isitici Aktif");
    isitici_durumu = true;
    digitalWrite(isitici, HIGH);
  }
  else
  {
    Serial.println("Isitici Pasif");
    isitici_durumu = false;
    digitalWrite(isitici, LOW);
  }

}

void soguk_su_beslemesi_kontrolu()
{
  if(sicaklik_degeri > 500)
  {
    Serial.println("Soguk Su Besleme Aktif");
    soguk_su_durumu = true;
    digitalWrite(soguksu_besleyici, HIGH);
  }
  else
  {
    Serial.println("Soguk Su Besleme Pasif");
    soguk_su_durumu = false;
    digitalWrite(soguksu_besleyici, LOW);
  }
}

void emniyet_valfi_kontrolu()
{
  if(basinc_degeri >500)
  {
    Serial.println("Emniyet Valfi Aktif");
    digitalWrite(emniyet_valfi, HIGH);
  }
  else
  {
    Serial.println("Emniyet Valfi Pasif");
    digitalWrite(emniyet_valfi, LOW);
  }
}

void karistirici_kontrolu()
{
  if(soguk_su_durumu == true || isitici_durumu == true)
  {
    Serial.println("Karistirici Aktif");
    digitalWrite(karistirici, HIGH);
  }
  else
  {
    Serial.println("Karistirici Pasif");
    digitalWrite(karistirici, LOW);
  }
}

void genel_sistem_kontrol()
{
  if(basinc_degeri < 250)
  {
    Serial.println("SISTEM BASLANGIC DURUMDA");
    digitalWrite(baslangic, HIGH);
    digitalWrite(normal, LOW);
    digitalWrite(alarm, LOW);
  }
  else if(basinc_degeri > 250 && basinc_degeri < 750)
  {
    Serial.println("SISTEM NORMAL DURUMDA");
    digitalWrite(baslangic, LOW);
    digitalWrite(normal, HIGH);
    digitalWrite(alarm, LOW);
  }
  else if(basinc_degeri > 750)
  {
    Serial.println("SISTEM ALARM DURUMUNDA");
    digitalWrite(baslangic, LOW);
    digitalWrite(normal, LOW);
    digitalWrite(alarm, HIGH);
  }
}
