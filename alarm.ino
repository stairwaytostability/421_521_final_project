/*
LiquidCrystal Library - TextDirection

Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
library works with all LCD displays that are compatible with the
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.

This sketch demonstrates how to use leftToRight() and rightToLeft()
to move the cursor.

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

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/LiquidCrystalTextDirection

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int ahour01;
int ahour10;
int aminute01;
int aminute10;
int ahour01pos = 9;
int ahour10pos = 8;
int aminute01pos = 12;
int aminute10pos = 11;

int select;
String digits;

//  if(voltage > 890 && voltage < 910){
//    Decrement();
//  }
//  if(voltage > 840 && voltage < 860){
//    MoveCursorLeft();
//  }
//  if(voltage > 800 && voltage < 830){
//    MoveCursorRight();
//  }
  

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // turn on the cursor:
  lcd.cursor();
  lcd.setCursor(0,2);
    lcd.print("Alarm - 00:00");
    Serial.begin(9600);
 
}

void loop() {

ahour01 = 6;
ahour10 = 0;
aminute01 = 6;
aminute10 = 4;  
String init = "Alarm - ";

digits = init + ahour10 + ahour01 + ":" + aminute10 + aminute01;
lcd.setCursor(0,2);
lcd.print(digits);

int voltage = analogRead(A0);
  if(voltage < 620){
    select = 1;
    lcd.cursor();
lcd.setCursor(aminute01pos,2);
  }
int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    int pos= 12;
while(select == 1){

Serial.println("Im in the while loop");
    
Serial.println(analogRead(A0));    
     if(analogRead(A0) > 840 && analogRead(A0) < 860){ //left button
      pos = pos -1;
      if(pos < 8){
        pos = 8;
      }
      lcd.setCursor(pos,2);
      
      }

  if(analogRead(A0) > 800 && analogRead(A0) < 830){ //right button
    pos = pos+1;
    if (pos > 12){
      pos = 12;
    }
    lcd.setCursor(pos,2);
 }

delay(500);
       if(analogRead(A0) < 620){
    select = 0;
  }
}
Serial.println("out of the loop");

delay(500);






// need to include use case for when hours and minutes are less than 10 - require a 0 in front of the value

  
//  // reverse directions at 'm':
//  if (thisChar == 'm') {
//    // go right for the next letter
//    lcd.rightToLeft();
//  }
//  // reverse again at 's':
//  if (thisChar == 's') {
//    // go left for the next letter
//    lcd.leftToRight();
//  }
//  // reset at 'z':
//  if (thisChar > 'z') {
//    // go to (0,0):
//    lcd.home();
//    // start again at 0
//    thisChar = 'a';
//  }
//  // print the character
//  lcd.write(thisChar);
//  // wait a second:
//  delay(1000);
//  // increment the letter:
//  thisChar++;
}








