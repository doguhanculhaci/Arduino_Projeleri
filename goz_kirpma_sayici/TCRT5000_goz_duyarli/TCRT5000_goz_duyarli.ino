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
