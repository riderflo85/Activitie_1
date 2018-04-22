
#include <IRremote.h>
#include <Stepper.h>

//Partie moteur;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
int nombreDePas = 48*64;
Stepper monMoteurD(nombreDePas,5,7,6,4);
Stepper monMoteurG(nombreDePas,9,11,10,8);
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int ledRouge = 3;
int pinMoteurA = 4;
int pinMoteurB = 5;
int pinMoteurC = 6;
int pinMoteurD = 7;
int pinMoteurE = 8;
int pinMoteurF = 9;
int pinMoteurG = 10;
int pinMoteurH = 11;

boolean etat; //pour vérifier et éviter que le plateau fasse 2 fois la meme action si on appuie 2 fois sur la meme touche
boolean etat2; //pour vérifier et éviter que le plateau fasse 2 fois la meme action si on appuie 2 fois sur la meme touche

const char DIN_RECEPTEUR_INFRAROUGE = 2; //Déclaration du pin du récepeteur infrarouge
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE); //Précise qu'on utilise un recepteur infrarouge
decode_results messageRecu; //Variable pour stocker le message reçu

void setup()
{
  //Partie moteur;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  monMoteurG.setSpeed(2);
  monMoteurD.setSpeed(2);
  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //Initialisation
 Serial.begin(9600);
 pinMode(ledRouge, OUTPUT);
 etat = true; //déclaration de l'état du plateau a "true (1)"
 etat2 = true;
 for (int n = 4; n < 12; n++)
 {
   pinMode(n, OUTPUT);
   }
 monRecepteurInfraRouge.enableIRIn(); //Activation du module infrarouge
 monRecepteurInfraRouge.blink13(true); //Pour faire clignoter la led de l'arduino a chaque réception de signal
}

void loop()
{
  if (monRecepteurInfraRouge.decode(&messageRecu)) //Pour détecter la présence/l'envoie d'un message
  {
    digitalWrite(ledRouge, HIGH);
    delay(150);
    if (messageRecu.value == 0xFF906F) { //Mettre en mode cinéma (enceinte tournées vers le lit) TOUCHE EQ (petite télécommande) TOUCHE DIY5 (télécommande LED)
      digitalWrite(ledRouge, LOW);
      if (etat == true) {
        monMoteurD.step(400);
        delay(1000);
        monMoteurG.step(400);
        etat = false;
        etat2 = false;
        for (int t = 4; t < 12; t++) {
          digitalWrite(t, LOW);
        }
      }//Mettre en mode cinéma (fin de de la condition)
     }
    else if (messageRecu.value == 0xFF629D) { //Fonction: si le mode cinéma est mit et que l'alim est ou a été débrancher et qu'on veut remettre en mode bureau TOUCHE CH petite telecommande
       digitalWrite(ledRouge, LOW);
       if (etat == true) {
        monMoteurD.step(-350);
        delay(500);
        monMoteurG.step(-400);
        etat2 = false;
        for (int t = 4; t < 12; t++) {
        digitalWrite(t, LOW);
        }
       }
      }

   if (messageRecu.value == 0xFFE01F) { //Mettre en mode Bureau (enceinte tournées vers le bureau) TOUCHE VOL- (petite télécommande) TOUCHE FADE7 (télécommande LED)
    digitalWrite(ledRouge, LOW);
    if (etat == false) {
      if (etat2 == false) {
       monMoteurD.step(-350);
      delay(500);
      monMoteurG.step(-400);
      etat = true;
      etat2 = true;
      for (int t = 4; t < 12; t++){
        digitalWrite(t, LOW);
      } 
     }
    }
   } // Mode Bureau (fin de la condition)
   else if (messageRecu.value == 0xFFE21D) { //Fonction pour ajuster la position des plateaux SANS SECURTITE!!!!!!!!! TOUCHE CH+
    digitalWrite(ledRouge, LOW);
    monMoteurD.step(100);
    delay(500);
    monMoteurG.step(100);
    for (int t = 4; t < 12; t++) {
      digitalWrite(t, LOW);
    }
   }
   else if (messageRecu.value == 0xFFA25D) { //Fonction pour ajuster la position des plateaux SANS SECURTITE!!!!!!!!! TOUCHE CH+
    digitalWrite(ledRouge, LOW);
    monMoteurD.step(-100);
    delay(500);
    monMoteurG.step(-100);
    for (int t = 4; t < 12; t++) {
      digitalWrite(t, LOW);
    }
   }
    
    monRecepteurInfraRouge.resume(); //Pour recevoir de nouveau message
  }
  else {
    digitalWrite(ledRouge, LOW);
    }
  delay(1);
}
