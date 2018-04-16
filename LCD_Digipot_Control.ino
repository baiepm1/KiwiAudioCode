#include <SPI.h>
#include <LiquidCrystal.h>

byte address = 0x00;
int CS = 10;
const int rs = 1, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Dec = 9;
const int Inc = 8;
int buttonstate_1 = 0;
int buttonstate_2 = 0;
int vol = 50;
int temp = 120;


void setup()
{
  pinMode(Dec, INPUT);
  pinMode(Inc, INPUT);

  lcd.begin(16,2);
  lcd.home();
  lcd.print("KIWI AUDIO .");
  delay (1200);
  lcd.print(".");
  delay (1000);
  lcd.print(".");
  delay (1000);
  pinMode (CS, OUTPUT);
  SPI.begin();
}

void loop()
{
  lcd.clear();
  //lcd.noCursor();
  lcd.setCursor(0,0);
  lcd.print("Volume: ");
  lcd.print(setVol()/10);
  delay(150);
 
  

}

int setVol()
{
  buttonstate_1 = digitalRead(Inc);
  buttonstate_2 = digitalRead(Dec);

  while (buttonstate_1 == HIGH)
  {
    if (vol < 120){
      vol += 10;
      digitalPotWrite(vol);
      delay(50);
    }
    break;
  }


  while (buttonstate_2 == HIGH)
  {
    if (vol > 0){
      vol -= 10;
      digitalPotWrite(vol);
      delay(50);
    }
    break;
  }
  return vol;
}

int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
