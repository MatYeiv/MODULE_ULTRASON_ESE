#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int lecture_temp = A0, lecture1 = A1, lecture2 = A2, lecture3 = A3;                               // Variables de lectures, se referant aux pins analogiques

int sortie_temp = 6,sortie1 = 5, sortie2 = 4, sortie3 = 3;                                        // Variables indiquant les pins de sorties en 0-5V

float valeur1 = 0, valeur2 = 0, valeur3 = 0;                                                      // Variables d'analyses dans les conditions

const float SEUIL_TENSION = 2.4, SEUIL_BAS_TEMPERATURE = 25.0,SEUIL_HAUT_TEMPERATURE = 27.0;      // Valeurs de seuils

int memoire = 0;                                                                                  // Variable de mémorisation pour la gestion de l'hystérésis

const int echantillon = 40;                                                                      // Variables déterminants le nombres d'échantillon dans la moyenne

int compteur = 0;                                                                                 // Compteur afin de gérer l'indexage du tableau

float tab_temperatures[echantillon], valeur_temp = 0, val_temp_total = 0;                         // Tableau de valeur de la température, somme des valeurs mesurée, et moyenne

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
                                                                                                  // Paramètrages des pins utilisés
  for(int j = 0; j < echantillon; j++)                                                            // Mise à zéro de toutes les valeurs du tableau
  {
    tab_temperatures[j] = 0;
  }
                                                                                                  // Selection des modes des pins de sorties
  delay(500);
}

void loop() {

  val_temp_total = val_temp_total - tab_temperatures[compteur];                                   // Soustraction de l'echantillon précédent

  tab_temperatures[compteur] = analogRead(lecture_temp)*5.0*100.0/1023.0;                         // Lecture du capteur

  val_temp_total = val_temp_total + tab_temperatures[compteur];                                   // Ajout du dernier echantillon

  Serial.print("Temperature: ");
  Serial.println(tab_temperatures[compteur]);
  Serial.print("Moyenne: ");
  Serial.println(valeur_temp);

  compteur = (compteur + 1) % echantillon;                                                        // Incrémentation de l'indice et vérification afin de savoir si l'on est à la fin du tableau

  valeur_temp = val_temp_total / echantillon;                                                     // Calcul de la moyenne
      
  lcd.setCursor(11,0);
  lcd.print(valeur_temp);
  
  valeur1 = analogRead(lecture1)*(5.0/1023);                                                      // Lecture des tensions dans les pins analogiques
  valeur2 = analogRead(lecture2)*(5.0/1023);                                                      // Et conversion en une valeur de tension
  valeur3 = analogRead(lecture3)*(5.0/1023);                                                      // Afin dêtre ensuite comparé au seuil

  Serial.print("Temperature: ");
  Serial.println(tab_temperatures[compteur]);
  //Serial.print("Moyenne: ");
  //Serial.println(valeur_temp);
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
  if((valeur_temp > SEUIL_HAUT_TEMPERATURE) || memoire == 1 )                                     // Memoire dans la condition permet le maintien de l'état haut sur la sortie tant que la température basse n'est pas atteinte
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
