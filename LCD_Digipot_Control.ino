#include <SPI.h>
#include <LiquidCrystal.h>
#include <RN52.h>
byte address = 0x00;
int CS_Vol = 10;
int CS_Gain=22;
int CS_Bass=24;
const int rs = 1, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Dec = 9;
const int Inc = 8;
int buttonstate_1 = 0;
int buttonstate_2 = 0;
int buttonchange = 7;
int buttonPushCounter = 1;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int vol = 50;
int Gain = 50;
int temp = 120;
RN52 rn52(10,11);    //Set RX to 10 and TX to 11

void setup()
{
  pinMode(Dec, INPUT);
  pinMode(Inc, INPUT);
  pinMode(buttonchange,INPUT);
  lcd.begin(16,2);
  lcd.home();
  lcd.print("KIWI AUDIO .");
  delay (1200);
  lcd.print(".");
  delay (1000);
  lcd.print(".");
  delay (1000);
  pinMode (CS_Vol, OUTPUT);
  pinMode (CS_Gain,OUTPUT);
  SPI.begin();
  rn52.begin(38400); 
}

void loop()
{
 buttonstate_1 = digitalRead(Inc);
 buttonstate_2 = digitalRead(Dec);
 buttonState =  digitalRead(buttonchange);


      if(buttonState == HIGH)
    {
    
    
    lcd.clear();
    lcd.noCursor();
    lcd.setCursor(0,0);
    buttonPushCounter++;
    delay(150);
    
     }
     else if(buttonPushCounter > 3 )
    {
      buttonPushCounter=1;
    }
  
    if (buttonPushCounter == 1) {
  lcd.clear();
  lcd.noCursor();
  lcd.setCursor(0,0);
  lcd.print("Volume: ");
  lcd.print(setVol()/10);
  delay(150);
  }else if (buttonPushCounter == 2)
  {
  lcd.clear();
  lcd.noCursor();
  lcd.setCursor(0,0);
  lcd.print("Gain: ");
 lcd.print(setGain()/10);
 delay(150);
  }
 else if (buttonPushCounter == 3)
 {
 lcd.clear();
 lcd.noCursor();
 lcd.setCursor(0,0);
  String Title = rn52.trackTitle();
 lcd.print(Title);
  lcd.print("Kiwi Audio");
 delay(150);
 }
 else
 lcd.clear();
 lcd.noCursor();
 lcd.print("Kiwi Audio");
}
  



int setVol()
{
  buttonstate_1 = digitalRead(Inc);
  buttonstate_2 = digitalRead(Dec);
  
  while (buttonstate_1 == HIGH)
  {
    if (vol < 120){
      vol += 10;
      digitalPotWrite_Vol(vol);
      delay(50);
    }
    break;
  }


  while (buttonstate_2 == HIGH)
  {
    if (vol > 0){
      vol -= 10;
      digitalPotWrite_Vol(vol);
      delay(50);
    }
    break;
  }
  return vol;
}

int setGain()
{
  buttonstate_1 = digitalRead(Inc);
  buttonstate_2 = digitalRead(Dec);
  
  while (buttonstate_1 == HIGH)
  {
    if (Gain < 120){
      Gain += 10;
      digitalPotWrite_Gain(Gain);
      delay(50);
    }
    break;
  }


  while (buttonstate_2 == HIGH)
  {
    if (Gain > 0){
      Gain -= 10;
      digitalPotWrite_Gain(Gain);
      delay(50);
    }
    break;
  }
  return Gain;
}



int digitalPotWrite_Vol(int value)
{
  digitalWrite(CS_Vol, LOW);
  SPI.transfer(0);
  SPI.transfer(value);
  digitalWrite(CS_Vol, HIGH);
}

int digitalPotWrite_Gain(int value)
{
  digitalWrite(CS_Gain, LOW);
  SPI.transfer(0);
  SPI.transfer(value);
  digitalWrite(CS_Gain, HIGH);
}
