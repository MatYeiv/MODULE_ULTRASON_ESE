#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int lecture1 = A1, lecture2 = A2, lecture3 = A3;

int sortie1 = 5, sortie2 = 4, sortie3 = 33;

float valeur1 = 0, valeur2 = 0, valeur3 = 0;

const float SEUIL_TENSION = 2.4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("Temp en "); lcd.print((char)223); lcd.print("C : ");

  lcd.setCursor(0, 1);
  lcd.print("P1:  ");

  lcd.setCursor(6, 1);
  lcd.print("P2:  ");

  lcd.setCursor(12, 1);
  lcd.print("P3:  ");

  pinMode(sortie1, OUTPUT);

  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  valeur1 = analogRead(lecture1)*(5.0/1023); // Lecture des tensions dans les pins analogiques
  valeur2 = analogRead(lecture2)*(5.0/1023); // Et conversion en une valeur de tension
  valeur3 = analogRead(lecture3)*(5.0/1023); // Afin dêtre ensuite comparé au seuil

  Serial.println(valeur1);
  
  if(valeur1 > SEUIL_TENSION)
  {
    lcd.setCursor(3, 1);
    lcd.print("p");
    digitalWrite(sortie1, HIGH);
  }
  else
  {
    lcd.setCursor(3, 1);
    lcd.print("a");
    digitalWrite(sortie1, LOW);  
  }

  delay(100);

}
