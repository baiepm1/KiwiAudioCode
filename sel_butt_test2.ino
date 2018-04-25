#include <SPI.h>
#include <LiquidCrystal.h>
//#include <Bounce2.h>

byte address = 0x00;
int CS = 10;
const int rs = 1, en = 6, d4 = 5, d5 = 4, d6 = 0, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Inc = 8; // button to increment Pin 8
const int Dec = 9; // button to decrement
const int sel = 11; // button used to select function Pin 11
int displayScreen = 0;
int vol = 50; // default volume
int bass = 50; // default bass
int gain = 50; // default gain
int buttonstate_1 = 0; 
int buttonstate_2 = 0;
int switchState = 0;
int prevSwitchState = 0;
static int hits = 0;
int counter = 0;
int state = 10;


void setup() {
  // put your setup code here, to run once:
 pinMode(sel, INPUT);
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
  lcd.clear();
  SPI.begin();  
}

void loop() 
{
  int switchState = digitalRead(sel);
  if (switchState != prevSwitchState) {
    if (switchState == HIGH) {
      hits = hits + 1;
      delay(10);
    }
  }

  if (hits == 1)
  {
   // lcd.clear();
    lcd.print("Volume: ");
    lcd.print(setVol()/10);
    delay(5);
    setVol();
  }
  else
  if (hits == 2)
  {
    lcd.setCursor(0,1);
    lcd.print("Bass:");
    lcd.print(setBass()/10);
    delay(5);
    setBass();
  }else
  if (hits == 3)
  {
    lcd.setCursor(8,1);
    lcd.print(" Gain:");
    lcd.print(setGain()/10);
    delay(5);
    setGain();
  }else
  if (hits >= 4)
  {
    hits = 0;
    Serial.println("counter is reset:");
  }
  Serial.println("..............");
  delay(50);
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

int setBass() {
    buttonstate_1 = digitalRead(Inc);
    buttonstate_2 = digitalRead(Dec);

    while (buttonstate_1 == HIGH) {
      if (bass < 120) {
        bass += 10;
        digitalPotWrite(bass);
        delay(50);
      }
      break;
    }
    while (buttonstate_2 == HIGH) {
      if (bass > 0) {
        bass -= 10;
        digitalPotWrite(bass);
        delay(50);
      }
      break;
    }
    return bass;
  }
int setGain() {
    buttonstate_1 = digitalRead(Inc);
    buttonstate_2 = digitalRead(Dec);

    while (buttonstate_1 == HIGH) {
      if (gain < 120) {
        gain += 10;
        digitalPotWrite(gain);
        delay(50);
      }
      break;
    }
    while (buttonstate_2 == HIGH) {
      if (gain > 0) {
        gain -= 10;
        digitalPotWrite(gain);
        delay(50);
      }
      break;
    }
    return gain;
  }
int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}


