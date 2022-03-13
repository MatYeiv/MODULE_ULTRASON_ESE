#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int lecture1 = A4;
int lecture2 = A3;
int lecture3 = A2;
int lect_Temp = A1;

float valeur1 = 0;
float valeur2 = 0;
float valeur3 = 0;
float val_Temp = 0;

int sortie1 = 3;
int sortie2 = 4;
int sortie3 = 5;
int sort1_Temp = 10;
int sort2_Temp = 11;
int sort_transi = 12;

float seuil_Haut = 2.4; // Seuil de tension en Volts
float tempMax = 30; // Température Max en °C
float tempMin = 20; // Température Min en °C

void setup()
{
  Serial.begin(9600); // Ouverture du moniteur série
  lcd.begin(16, 2); // initialisation de l'écran
  //Indication du mode dans lequel les pins de l'arduino doivent être
  pinMode(sortie1, OUTPUT);
  pinMode(sortie2, OUTPUT);
  pinMode(sortie3, OUTPUT);
  pinMode(sort1_Temp, OUTPUT);
  pinMode(sort2_Temp, OUTPUT);
  pinMode(sort_transi, OUTPUT);
}

void loop()
{
  valeur1 = analogRead(lecture1)*(5.0/1023); // Lecture des tensions dans les pins analogiques
  valeur2 = analogRead(lecture2)*(5.0/1023); // Et conversion en une valeur de tension
  valeur3 = analogRead(lecture3)*(5.0/1023); // Afin dêtre ensuite comparé au seuil
  
  val_Temp = ((analogRead(lect_Temp)*((5.0)/1023)- 0.5)*100); // Lecture de la température et conversion en °C

  lcd.setCursor(0,0); // Dépalacement du cursor en position (0, 0)
  lcd.print("Temp en "); lcd.print((char)223); lcd.print("C : "); lcd.print(val_Temp);
  
  Serial.println(val_Temp);
  
// Lecture du capteur en Position 1
  if (valeur1 > seuil_Haut)
  {
    digitalWrite(sortie1, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("P1:p");
  }
  else
  {
    digitalWrite(sortie1, LOW);
    lcd.setCursor(0, 1);
    lcd.print("P1:a");
  }
// Lecture du capteur en Position 2
  if (valeur2 > seuil_Haut)
  {
    digitalWrite(sortie2, HIGH);
    lcd.setCursor(5, 1);
    lcd.print("P2:p");
  }
  else
  {
    digitalWrite(sortie2, LOW);
    lcd.setCursor(5, 1);
    lcd.print("P2:a");
  }
// Lecture du capteur en Position 3  
  if (valeur3 > seuil_Haut)
  {
    digitalWrite(sortie3, HIGH);
    lcd.setCursor(10, 1);
    lcd.print("P3:p");
  }
  else
  {
    digitalWrite(sortie3, LOW);
    lcd.setCursor(10, 1);
    lcd.print("P3:a");
  }
// Lecture du capteur de Température
  if(val_Temp > 30)
  {
    digitalWrite(sort1_Temp, HIGH);
    digitalWrite(sort2_Temp, LOW);
    digitalWrite(sort_transi, LOW);
  }
  else if(val_Temp < 20)
  {
    digitalWrite(sort1_Temp, LOW);
    digitalWrite(sort2_Temp, HIGH);
    digitalWrite(sort_transi, LOW);
  }
  else
  {
    digitalWrite(sort1_Temp, LOW);
    digitalWrite(sort2_Temp, LOW);
    digitalWrite(sort_transi, HIGH);
  }
  
  delay(100);
}
