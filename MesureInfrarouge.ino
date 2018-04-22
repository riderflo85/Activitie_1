#include <IRremote.h>
int pinLedRouge = 3;
int pinLedVerte = 4;

const char DIN_RECEPTEUR_INFRAROUGE = 3; //Déclaration du pin du récepeteur infrarouge

IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE); //Précise qu'on utilise un recepteur infrarouge

decode_results messageRecu; //Variable pour stocker le message reçu

void setup()
{
  //Initialisation
  pinMode(pinLedRouge, OUTPUT);
  pinMode(pinLedVerte, OUTPUT);
 Serial.begin(9600);
 monRecepteurInfraRouge.enableIRIn(); //Activation du module infrarouge
 monRecepteurInfraRouge.blink13(true); //Pour faire clignoter la led de l'arduino a chaque réception de signal
}

void loop()
{
  if (monRecepteurInfraRouge.decode(&messageRecu)) { //Pour détecter la présence/l'envoie d'un message    
    digitalWrite(pinLedRouge, HIGH);// Allume la led rouge a chaque fois qu'un bouton de la télécommande est presser
    Serial.println(messageRecu.value, HEX);//affiche la fréquence mesurer en Héxadécimale
    delay(150);
    Serial.print(messageRecu.value);

    monRecepteurInfraRouge.resume(); //Pour recevoir de nouveau message
  }
  else {
    digitalWrite(pinLedRouge, LOW);//Eteint la led rouge si le capteur infrarouge ne reçoit aucune fréquence/signal de la télécommande
    }
    
  delay(1);
}
