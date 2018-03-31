#include <SPI.h>
#include <LiquidCrystal.h>

byte address = 0x00;
int CS= 10;
const int rs = 12, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Dec = 9;
const int Inc = 8;

void setup()
{
pinMode(Dec, INPUT);
pinMode(Inc, INPUT);

  lcd.begin(16, 2);
   lcd.home();
  lcd.print("KIWI AUDIO .");
  lcd.display();
  delay (1200);
  lcd.print(".");
  delay (1000);
  lcd.print(".");
  delay (1000);
  ////////////
  lcd.home();
  lcd.print("Vol:");
  // Turn on the display:
  lcd.display();
  ///////////////
pinMode (CS, OUTPUT);
SPI.begin();
}
int buttonstate_1=0;
int buttonstate_2=0;
int light = 0;
int temp=120;
void loop()
{
buttonstate_1=digitalRead(Inc);
buttonstate_2=digitalRead(Dec);

lcd.home();
lcd.print("Vol:" + String(light));
  
if(buttonstate_1 == HIGH)
{
  light+=10;
  digitalPotWrite(light);
  lcd.home();
  lcd.print("Vol:" + String(light));
}
 else
{
  digitalPotWrite(light);
}

if(buttonstate_2 == HIGH)
{
  light-=10;
  lcd.home();
  lcd.print("Vol:" + String(light));
  digitalPotWrite(light);
}
 else
{
  digitalPotWrite(light);
}

}

int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
