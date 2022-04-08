
/*
  LiquidCrystal Library - Blink

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and makes the
 cursor block blink.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
   * ends to +5V and ground
   * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalBlink

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Rtc_Pcf8563.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Rtc_Pcf8563 rtc;

unsigned long t;
unsigned long LastTime=0;
unsigned long CurrentTime;
int sensormag=0;
int vhelp=0;
int ileobr=0;
double przebytadroga=0;
double r=0.37;
double v;
double v1;
double v2;
double vmax=0;
double o;
float t1;
float t2;
boolean pushbuttonState=LOW;
boolean pushbuttonState1=LOW;
boolean currentbuttonState=LOW;
boolean currentbuttonState1=LOW;
int DisplayMode;

double obwod(double r);

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  //rtc.begin();
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(9, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  lcd.clear();
  lcd.setCursor(6, 0);

  // Print a message to the lcd.
  lcd.print("km/h");
  lcd.setCursor(0, 0);

  lcd.setCursor(10,0);
  lcd.print(vmax);
  lcd.setCursor(0,0);
  lcd.setCursor(5,1);
  lcd.print("km");
  lcd.setCursor(0,0);

  //clear out all the registers
  //rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century, year
  //rtc.setDate(12, 6, 12, 0, 20);
  //hr, min, sec
  //rtc.setTime(19, 16, 30);
  
}

void loop() {
    sensormag==LOW;
    CurrentTime = millis();
    sensormag=digitalRead(8);
    currentbuttonState=debounce(pushbuttonState, 7);
    currentbuttonState1=debounce(pushbuttonState, 9);
    if(currentbuttonState==HIGH)
    {
                DisplayMode=1;
    }
    if(currentbuttonState1==HIGH)
    {
                DisplayMode=2;
    }

  if(sensormag==LOW){
    sensormag==HIGH;
    if(CurrentTime-LastTime>150){
    if(LastTime>0)
    {
  t=CurrentTime-LastTime;
  t1=float(t)/1000;
  //Serial.println(float(CurrentTime)/1000);
  o=obwod(r);
  v=o/t1;
  v1=v*3600;
  v2=v1/1000;
  Serial.println(v2);
  if(v2<140)
  {
  ileobr++;
  przebytadroga=(ileobr*o)/1000; 
  Serial.println(przebytadroga); 
    if(vmax<v2)
    {
    vmax=v2;
    }
  }
  else
  {
    v2=0;
  }
  //delay(50);
  LastTime=CurrentTime;
    }
  else
  {
    LastTime=CurrentTime;
  }
  }
  }
  else
  {
    if(CurrentTime-LastTime>2000){
    v=0;
    v1=v*3600;
    v2=v1/1000;
    }
  }

  t2=float(CurrentTime)/3600000;

  mode(DisplayMode, v2,vmax,przebytadroga, t2);

}

double obwod(double r)
{
  double wynik;
  wynik=2*3.14*r;
  return wynik;
}



void mode(int DisplayMode, double v2, double vmax, double przebytadroga, float t2) {

  switch (DisplayMode){
  case 1:
          lcd.setCursor(6, 0);

  // Print a message to the lcd.
  lcd.print("km/h");
  lcd.setCursor(0,0);
  lcd.setCursor(10,0);
  lcd.print(vmax);
  if(vmax==0)
  {
  lcd.print("  ");
  }
  lcd.setCursor(0,0);
  lcd.setCursor(5,1);
  lcd.print("km");
  lcd.setCursor(0,0);

  //v2

  lcd.setCursor(0, 0);  
  if(v2<140 && v2>0)
  {
  lcd.print(v2);
  if(przebytadroga<10)
  {
  lcd.setCursor(0, 1);
  lcd.print(przebytadroga);
  lcd.print(" ");
  lcd.setCursor(0,0);
  }
  if(przebytadroga<100)
  {
      lcd.setCursor(0, 1);
      lcd.print(przebytadroga);
      lcd.setCursor(0,0);
  }
  }
  if(v2==0)
  {
    lcd.setCursor(0, 0);
    lcd.print(v2);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print(przebytadroga);
    lcd.print(" ");
    lcd.setCursor(0,0);
  }

  //t2
  lcd.setCursor(8,1);
  lcd.print(t2);
  lcd.setCursor(0,0);
  lcd.setCursor(12,1);
  lcd.print("h");
  lcd.setCursor(0,0);  
    break;
  case 2:
    lcd.setCursor(0,0);
    lcd.print(rtc.formatTime());
    lcd.print("        ");
    lcd.setCursor(0, 1);
    lcd.print(rtc.formatDate());
    lcd.print("      ");
    break;
  }
}



boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if (last != current) {
    current = digitalRead(pin);
  }
  return current;
}
