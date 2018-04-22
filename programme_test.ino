#include <IRremote.h>
#include <Stepper.h>

//Partie moteur;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
int nombreDePas = 48*64;
Stepper monMoteur(nombreDePas,9,11,10,7);
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int ledVerte = 4;
int ledRouge = 3;
int pinMoteurA = 7;
int pinMoteurB = 9;
int pinMoteurC = 10;
int pinMoteurD = 11;

boolean etat; //pour vérifier et éviter que le plateau fasse 2 fois la meme action si on appuie 2 fois sur la meme touche

const char DIN_RECEPTEUR_INFRAROUGE = 2; //Déclaration du pin du récepeteur infrarouge
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE); //Précise qu'on utilise un recepteur infrarouge
decode_results messageRecu; //Variable pour stocker le message reçu

void setup()
{
  //Partie moteur;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  monMoteur.setSpeed(3);
  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //Initialisation
 Serial.begin(9600);
 pinMode(ledRouge, OUTPUT);
 pinMode(ledVerte, OUTPUT);
 etat = true; //déclaration de l'état du plateau a "true (1)"
 for (int n = 7; n < 12; n++)
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
    if (messageRecu.value == 0xFF906F) { //Mettre en mode cinéma (enceinte tournées vers le lit).
      digitalWrite(ledRouge, LOW);
      if (etat) {
        digitalWrite(ledVerte, HIGH);
        monMoteur.step(-500);
        etat = false;
        for (int t = 7; t < 12; t++) {
          digitalWrite(t, LOW);
        }
      }
     }//Mettre en mode cinéma (fin de de la condition)

   if (messageRecu.value == 0xFFE01F) { //Mettre en mode Bureau (enceinte tournées vers le bureau).
    digitalWrite(ledRouge, LOW);
    if (etat == false) {
      digitalWrite(ledVerte, HIGH);
      monMoteur.step(500);
      etat = true;
      for (int t = 7; t < 12; t++){
        digitalWrite(t, LOW);
      }
    }
   } // Mode Bureau (fin de la condition)
    
    monRecepteurInfraRouge.resume(); //Pour recevoir de nouveau message
  }
  else {
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVerte, LOW);
    }
  delay(1);
}
