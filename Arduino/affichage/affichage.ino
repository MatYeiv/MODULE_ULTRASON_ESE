#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
  // put your setup code here, to run once:

   lcd.begin(16, 2);
  
   lcd.setCursor(0, 0);
   lcd.print("Temp en "); lcd.print((char)223); lcd.print("C : ");

   lcd.setCursor(0, 1);
   lcd.print("P1:  ");

   lcd.setCursor(6, 1);
   lcd.print("P2:a ");

   lcd.setCursor(12, 1);
   lcd.print("P3:a ");

   delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(3, 1);
  lcd.print((millis()/1000));

  delay(100);
}
