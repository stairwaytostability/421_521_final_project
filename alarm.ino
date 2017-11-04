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
  lcd.setCursor(0, 2);
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
  lcd.setCursor(0, 2);
  lcd.print(digits);

  int voltage = analogRead(A0);
  if (voltage < 620) {
    select = 1;
    lcd.cursor();
    lcd.setCursor(aminute01pos, 2);
    delay(250);
  }
  int left = 0;
  int right = 0;
  int up = 0;
  int down = 0;
  int pos = 12;
  while (select == 1) {

    Serial.println(analogRead(A0));
    if (analogRead(A0) > 840 && analogRead(A0) < 860) { //left button - move cursor left
      //pos = pos - 1;
      if (pos == 11) { //skip the colon
        pos = pos - 2;
      }
      else if (pos < 9) { //dont go past the hours
        pos = 8;
      }
      else {
        pos = pos - 1; //otherwise move left
      }
      lcd.setCursor(pos, 2); //set cursor
      delay(250);
    }

    if (analogRead(A0) > 800 && analogRead(A0) < 830) { //right button - move cursor right
      //pos = pos + 1;
      if (pos == 9) {
        pos = pos + 2;
      }
      else if (pos > 11) {
        pos = 12;
      }
      else {
        pos = pos + 1;
      }
      lcd.setCursor(pos, 2);
      delay(250);
    }

    if (analogRead(A0) > 890 && analogRead(A0) < 910) { //decrease value
      bool a = pos == aminute01pos; //check where the cursor is
      bool b = pos == aminute10pos;
      bool c = pos == ahour01pos;
      bool d = pos == ahour10pos;
      if (a) {
        if (aminute01 == 0) {
          aminute01 = 9; //cycle it back to top
        }
        else {
          aminute01 = (aminute01 - 1);
        }

      }
      else if (b) {
        if (aminute10 == 0) { //cycle it back to top
          aminute10 = 5;
        }
        else {
          aminute10 = (aminute10 - 1);
        }

      }
      else if (c) {
        if (ahour10 == 2 && ahour01 == 0) { //making it a 24 hour clock by checking what theother digit is
          ahour01 = 3;
        }
        else if (ahour10 != 2 && ahour01 == 0) {
          ahour01 = 9;
        }
        else {
          ahour01 = ahour01 - 1;
        }
      }
      else {
        if (ahour10 == 0) { //only part we need to fix here is that whenever the hour10 is set to 2, we should automatically set the cursor to the hour01 and change it to a reasonable value
          ahour10 = 2;      // alternatively, just don't let the user exit the set alarm state when an unreasonable time exists - error message might be easiest
        }
        else {
          ahour10 = ahour10 - 1;
        }
      }

      digits = init + ahour10 + ahour01 + ":" + aminute10 + aminute01;
      lcd.setCursor(0, 2);
      lcd.print(digits);
      delay(250);
      lcd.setCursor(pos, 2);
    }

    if (analogRead(A0) < 620) { //when you want to get out of the "setting alarm" stage, flash the display and get out of the while loop
      select = 0;
      for (int i = 0; i < 5; i++) {
        lcd.noDisplay();
        delay(150);
        lcd.display();
        delay(300);
      }
    }
  }

  delay(500);

}


