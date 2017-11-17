#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

 if (analogRead(A0) > 800 && analogRead(A0) < 830) { //right button - turn on alarm
  Serial.println("y");
 }

  if (analogRead(A0) > 850 && analogRead(A0) < 860) { //left button - turn off alarm
     // alarmOff = 1;
      Serial.println("k");
  }

  delay(200);
}
