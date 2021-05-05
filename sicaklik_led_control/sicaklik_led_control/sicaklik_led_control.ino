const int lm35Pin = 0; // data pinini belirliyoruz

float sicaklik; // Serial monitörden okuyacağımız sıcaklık değeri
float lm35Deger;

int kled = 4;
int mled = 3;

void setup(){
  
  Serial.begin(9600);
  
  pinMode(kled,OUTPUT);
  pinMode(mled,OUTPUT);
  
  pinMode(lm35Pin,INPUT); // lm35 data pinini çıkış olarak ayarladık

  digitalWrite(kled,LOW);
  digitalWrite(mled,LOW);
 
}

void loop(){
 
  lm35Deger=analogRead(lm35Pin); // data bacagındaki veriyi okuduk
  lm35Deger=(lm35Deger*4.88)-500; // degeri mV 'a dönüştürecek
  sicaklik=lm35Deger/10.0; // sıcaklık başına 10mV üreteceği ifade
 
  Serial.print("sicaklik : ");
  Serial.print(sicaklik);
  Serial.println(" derece");
  
  if(sicaklik>40)
  {
    digitalWrite(mled,LOW);
    digitalWrite(kled,HIGH);
    
  }
  else if(sicaklik < 0)
  {
    digitalWrite(mled,HIGH);
    digitalWrite(kled,LOW);
  }
  else
  {
    digitalWrite(mled,LOW);
    digitalWrite(kled,LOW);
  }
  
}
