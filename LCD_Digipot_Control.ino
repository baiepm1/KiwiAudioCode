

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
     delay (1000);
  //lcd.print("Vol:10   Bass:69");
  // lcd.setCursor(0, 1);
  //lcd.print("Gain:00");
  // Turn on the display:
  lcd.display();
  ///////////////
  
pinMode (CS, OUTPUT);
SPI.begin();
}
int buttonstate_1=0;
int buttonstate_2=0;
int light=0;
int temp=120;

void loop()
{
setBrightiness();

}

void setBrightiness()
{
  buttonstate_1=digitalRead(Inc);
buttonstate_2=digitalRead(Dec);

while (buttonstate_1 == HIGH)
{
  
 if (light < 120)
  {
    light+=10;
    digitalPotWrite(light);
   // lcd.autoscroll();
    lcd.setCursor(0,0);
    lcd.print("Resistor: ");
    lcd.print(String(light)); 
    //lcd.print("               ");
    delay(50);
    //lcd.noAutoscroll();
  }
  break;
}


while(buttonstate_2 == HIGH)
{
  if (light >0)
  {
    light-=10;
  digitalPotWrite(light);   
  lcd.setCursor(0,0);
    lcd.print("Resistor: ");
    lcd.print(String(light)); 
    //lcd.print("               ");
    delay(50);

  delay(50);
  }
break;
}

}
int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
