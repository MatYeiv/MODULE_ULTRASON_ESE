#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int lecture_temp = A0, lecture1 = A1, lecture2 = A2, lecture3 = A3;                               // Variables de lectures, se referant aux pins analogiques

int sortie_temp = 6,sortie1 = 5, sortie2 = 4, sortie3 = 3;                                        // Variables indiquant les pins de sorties en 0-5V

float valeur_temp = 0, valeur1 = 0, valeur2 = 0, valeur3 = 0;                                     // Variables d'analyses dans les conditions

const float SEUIL_TENSION = 2.4, SEUIL_BAS_TEMPERATURE = 23.0,SEUIL_HAUT_TEMPERATURE = 25.0;      // Valeurs de seuils

int memoire = 0;

void setup() {

  Serial.begin(9600);                                                                             // Ouverture du port serie permettant d'afficher des variables sur l'ordinateur
  lcd.begin(16, 2);                                                                               // Initialisation de l'écran
  
  lcd.setCursor(0, 0);
  lcd.print("Temp en "); lcd.print((char)223); lcd.print("C: ");

  lcd.setCursor(0, 1);
  lcd.print("P1:a ");

  lcd.setCursor(6, 1);
  lcd.print("P2:a ");

  lcd.setCursor(12, 1);
  lcd.print("P3:a ");
                                                                                                  // Écriture des textes fixes
  pinMode(sortie_temp, OUTPUT);
  pinMode(sortie1, OUTPUT);
  pinMode(sortie2, OUTPUT);
  pinMode(sortie3, OUTPUT);
                                                                                                  // Selection des modes des pins de sorties
  delay(500);

}

void loop() {

  valeur_temp = analogRead(lecture_temp)*5.0*100.0/1023.0;                                        // Lecture de la valeur de température

  lcd.setCursor(11,0);
  lcd.print(valeur_temp);
  
  valeur1 = analogRead(lecture1)*(5.0/1023);                                                      // Lecture des tensions dans les pins analogiques
  valeur2 = analogRead(lecture2)*(5.0/1023);                                                      // Et conversion en une valeur de tension
  valeur3 = analogRead(lecture3)*(5.0/1023);                                                      // Afin dêtre ensuite comparé au seuil

  Serial.println(valeur_temp);
                                                                                                  // Comparaison de la valeur du capteur 1 
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
                                                                                                   // Comparaison de la valeur du capteur 2
  if(valeur2 > SEUIL_TENSION)
  {
    lcd.setCursor(9, 1);
    lcd.print("p");
    digitalWrite(sortie2, HIGH);
  }
  else
  {
    lcd.setCursor(9, 1);
    lcd.print("a");
    digitalWrite(sortie2, LOW);  
  }
                                                                                                  // Comparaison de la valeur du capteur 3
  if(valeur3 > SEUIL_TENSION)
  {
    lcd.setCursor(15, 1);
    lcd.print("p");
    digitalWrite(sortie3, HIGH);
  }
  else
  {
    lcd.setCursor(15, 1);
    lcd.print("a");
    digitalWrite(sortie3, LOW);  
  }
                                                                                                  // Comparaison de la valeur de température
  if((valeur_temp > SEUIL_HAUT_TEMPERATURE) || memoire == 1 )                                     // Memoire dans la condition permet le maintien de l'état haut dur la sortie tant que la température basse n'est pas atteinte
  {
    digitalWrite(sortie_temp, HIGH);

  }
  else
  {
    digitalWrite(sortie_temp, LOW);
  }
                                                                                                  // Comparaison permettant de gérer l'hystéresis
  if ((valeur_temp > SEUIL_HAUT_TEMPERATURE))
  {
    memoire = 1;
  }
  else if (valeur_temp < SEUIL_BAS_TEMPERATURE)
  {
    memoire = 0;
  }
  
  delay(100);
}
