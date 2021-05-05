# hex_to_binnary_LED_ON

## Devre Şeması
![image](https://user-images.githubusercontent.com/53540561/117132240-3a0ee680-adab-11eb-94cb-8ee1c2742521.png)

## Açıklama
Öncelikle D1D0 ve D3D2 adında iki sabit değer tanımladık. Bunlar senin ID’ nin son 4 haneleridir. Bu tanımlama isimlerini hocan kendi belirtmiş.
Daha sonra sonuç bir hex türünde olucak örnek; 78+56 = 134 bu değeri ben sonuç şeklinde bir int değerin içine atadım. Bu değer HEX türünde dir.
Led pin degerlerinide hızlı bir şekilde atamak için int ledPin[] = {2,3,4,5,6,7,8,9}; bu yolu kullandım.
Setup kısmında kurulumumuzu yaptık. Ben hızlı olması için bir for döngüsü koyup i yi arttırarak digital pinlerin atamasını bu şekilde yaptım. Ve OUTPUT yazarak bunların birer 5V çıkışı olacağını işlemcime bildirdim.
Loop döngüsünde dışarıdaki bir fonksiyona sonuc adında ki değerimi yolladım.

Dışarıdaki fonksiyonum yani void displayBinary(byte numToShow) kısmında gelen sonuç değerini numToShow adında bir byte tipinde yazdırdım. Bu sayede gelen sonuç değerim bir BİN tipine dönüşmüş oldu. Bu numToShow ismini ben koydum dilersen bunun ismini değiştirebilirsin.

Daha sonrada for döngümde bi i değerini devamlı olarak arttırdım ve Bin türüne çevirdiğimiz sayının tüm değerlerini tek tek gezdim. Bunuda bitRead(numToShow,i) de gerçekleştirdim. İ sayısı her arttığında bir sonraki değeri kontrol etmiş oldum. Ve kontrol ettiğimde eğer o 1 ise onun ait olduğu ledi yaktım. Eğer 0 ise söndürdüm. Bütün olay bu. 


## Arduino Kodları
```
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
{![image](https://user-images.githubusercontent.com/53540561/117132244-3b401380-adab-11eb-908e-559dc2958786.png)

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
```
