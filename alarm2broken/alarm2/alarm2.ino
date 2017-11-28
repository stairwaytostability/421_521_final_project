
// include the library code:
#include <LiquidCrystal.h> // library for LCD
#include <Time.h>
#include <TimeLib.h>

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int ahour01 = 0; // units place of alarm hour
int ahour10 = 0; // tens place of alarm hour
int aminute01 = 0;
int aminute10 = 0;
int ahour01pos = 9; // position of the alarm hour units place on the LCD display
int ahour10pos = 8;
int aminute01pos = 12;
int aminute10pos = 11;
int alarm = 0;

int select; // used to enter alarm-setting mode
String digits; // full alarm time string
bool match; // boolean for whether or not alarm time and clock time match
String read_serial; // clock time read from pi
String read_serialNew;
bool alarmOff = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // turn on the cursor:
  lcd.cursor();
  lcd.setCursor(0, 2);
  String init = "Alarm - ";

  digits = init + ahour10 + ahour01 + ":" + aminute10 + aminute01; // assemble alarm time string
  lcd.setCursor(0, 2);
  lcd.print(digits);
  lcd.noCursor();

  Serial.begin(9600); // initialize serial communication
//delay(500);
  read_serial = Serial.readString(); // read communication from pi (clock time)
}

void loop() {

  if (Serial.available() > 0) {
    // read the incoming string
    read_serialNew = Serial.readString();
    if (read_serialNew.length() > 13) { // make sure multiple strings don't print 
                                        // when the clock is paused for setting the alarm
      read_serialNew = read_serialNew.substring(0, 12) ;
    }

    if (read_serialNew.substring(8, 13) != read_serial.substring(8, 13)) { // when there is a new clock time, compare it to alarm time
      String alarmtime = digits.substring(8, 13);
      String clocktime = read_serialNew.substring(8, 13);
      match = alarmtime == clocktime; // if the clock time and alarm time match, match == 1

      while (match && !alarmOff) { // while a match is present, but the alarm hasn't been turned off yet
        Serial.println("y"); // send a y to the pi to tell it the alarm is on and initiate youtube video
        for (int i = 0; i < 3; i++) { // flash the LCD screen to indicate the alarm is going off
          lcd.noDisplay();
          delay(50);
          lcd.display();
          delay(50);
        }
        if (analogRead(A0) > 850 && analogRead(A0) < 860) { // left button press detected - turn off alarm and break from while loop
          Serial.println("k");
          alarmOff = 1;
          break;

        }
      }
    }
    read_serial = read_serialNew; // update read_serial
  }

  lcd.cursor();
  lcd.home();
  lcd.print(read_serial); // print updated clock time on LCD
  lcd.noCursor();

  String init = "Alarm - ";
  int voltage = analogRead(A0);


  // enter SET ALARM mode if select button is pressed

  if (voltage < 620) { // analog voltage when select button is pressed
    select = 1;
    lcd.cursor(); // display cursor for alarm setting
    lcd.setCursor(aminute01pos, 2);
    delay(250);
  }

  int pos = 12;
  while (select == 1) {
    alarmOff = 0;

    //MOVE LEFT

    if (analogRead(A0) > 850 && analogRead(A0) < 860) { //left button - move cursor left
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

    //MOVE RIGHT

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

    //DECREASE VALUE

    if (analogRead(A0) > 900 && analogRead(A0) < 905) { //decrease value
      bool a = pos == aminute01pos; //check where the cursor is
      bool b = pos == aminute10pos;
      bool c = pos == ahour01pos;

      if (a) {
        aminute01 = ((aminute01 - 1) + 10) % 10; // this addition of 10 to the modulus accounts for negative numbers b/c 0 is 
      }                                           // the critical value for decreasing the digit
      else if (b) {
        aminute10 = ((aminute10 - 1) + 6) % 6;
      }
      else if (c) {
        if (ahour10 == 2 && ahour01 == 0) { //making it a 24 hour clock by checking what the other digit is
          ahour01 = 3;
        }
        else {
          ahour01 = ((ahour01 - 1) + 10) % 10;
        }
      }
      else {
        ahour10 = ((ahour10 - 1) + 3) % 3;
      }

      digits = init + ahour10 + ahour01 + ":" + aminute10 + aminute01;
      lcd.setCursor(0, 2);
      lcd.print(digits);
      lcd.noCursor();
      delay(250);
      lcd.setCursor(pos, 2);
      lcd.cursor();
    }

    //INCREASE VALUE
    if (analogRead(A0) > 927 && analogRead(A0) < 931) {
      bool a = pos == aminute01pos; //check where the cursor is
      bool b = pos == aminute10pos;
      bool c = pos == ahour01pos;

      if (a) {
        aminute01 = (aminute01 + 1) % 10;
      }
      else if (b) { //cycle it back to top
        aminute10 = (aminute10 + 1) % 6;
      }
      else if (c) {
        if (ahour10 == 2 && ahour01 == 3) { //making it a 24 hour clock by checking what the other digit is
          ahour01 = 0;
        }
        else {
          ahour01 = (ahour01 + 1) % 10;
        }
      }
      else {
        ahour10 = (ahour10 + 1) % 3;
      }
      digits = init + ahour10 + ahour01 + ":" + aminute10 + aminute01;
      lcd.setCursor(0, 2);
      lcd.print(digits);
      lcd.noCursor();
      delay(250);
      lcd.setCursor(pos, 2);
      lcd.cursor();
    }

    //GET OUT OF ALARM SET

    if (analogRead(A0) < 620) { // when you want to get out of the "setting alarm" stage, flash the display and get out of the while loop
      if (ahour10 == 2 && ahour01 > 3) {
        select = 1;
        lcd.clear(); // when clearing the screen, remember to put the time back on the first line after the error message
        lcd.setCursor(0, 2);
        lcd.print("Invalid time!"); // error handling for putting impossible times (ex. 29:00)
        lcd.noCursor();
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 2);
        lcd.print(digits);
        lcd.setCursor(pos, 2);
        lcd.cursor();
      }
      else {
        select = 0;
        // flash the display to show that the alarm is set
        for (int i = 0; i < 5; i++) {
          lcd.noDisplay();
          delay(150);
          lcd.display();
          delay(300);
        }
        lcd.noCursor(); //get rid of cursor because alarm setting is complete
      }

    }
  } //end of while loop for setting alarm
}




