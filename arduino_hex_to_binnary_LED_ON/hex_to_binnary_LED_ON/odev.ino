#define D1D0  78
#define D3D2  56

int sonuc = D1D0 + D3D2;

int ledPin[] = {2,3,4,5,6,7,8,9};

void setup()
{
  for(int i = 0; i < 9; i++)
  {
    pinMode(ledPin[i],OUTPUT);
  }
}

void loop()
{
  displayBinary(sonuc);
}

void displayBinary(byte numToShow)
{
  for(int i = 8; i > 0; i--)
  {
    if(bitRead(numToShow, i) == 1)
    {
      digitalWrite(ledPin[i],HIGH);
    }
    else
    {
     digitalWrite(ledPin[i],LOW); 
    }
  }
}
