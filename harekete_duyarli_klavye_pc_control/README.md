# harekete_duyarlı_klavye_pc_control

## Devre Şeması
![image](https://user-images.githubusercontent.com/53540561/117134982-046bfc80-adaf-11eb-918e-d7eb47d52333.png)

## Açıklama

DAHA SONRA EKLENECEKTİR.

## Arduino Kodları
```
#include <Keyboard.h> 

int dakika = 0;
int saniye = 0;

int pirPin = 9;
bool hareket_algilandi_mi = false;

void setup ()
{
Keyboard.begin ();
pinMode(pirPin, INPUT);
delay(1000);;
}

void loop ()
{
  hareket = digitalRead(pirPin);

  if(hareket == HIGH)
  {
    hareket_algilandi_mi = true;
  }

  if(hareket_algilandi_mi)
  {
    Keyboard.press (KEY_LEFT_CTRL);
    delay(100);
    Keyboard.press (KEY_LEFT_ALT);
    delay(100);
    Keyboard.println ('O');
    Keyboard.releaseAll ();
    delay(5000);
    
    Keyboard.println ('ASDASD');
    delay (100);
    Keyboard.write (KEY_RETURN);
    delay(1000);
    
    Keyboard.println ('f');
    delay (100);
    Keyboard.write (KEY_RETURN);

    for(int k = 0; k < saniye; k++)
    {
      delay(1000);
    }

    for(int i = 0; i <= dakika; i++)
    {
      for(int j = 0; j <= 60; j++)
      {
        delay(1000);
      }
    }

    Keyboard.press (KEY_LEFT_ALT);
    delay(100);
    Keyboard.press (KEY_F4);
    Keyboard.releaseAll ();

    hareket_algilandi_mi = false;
  }
}
```
