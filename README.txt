
Nom du projet: Plateau tournant commander par arduino et télécommande infrarouge
Support et language utilisé: Arduino
Date de création: 21/04/2018
Créateur: Florent

======================================================================================================
									INTRODUCTION

Avec se programme vous pourrez piloter deux moteur pas à pas avec une télécommande infrarouge

Seuls pré-requis:
	-Avoir des connaissances de base en arduino
	-Avoir le matéreils nécessaire (liste un peu plus bas)
	-Le logiciel Arduino doit être installé
	-Ajouter les librairies à vôtre logiciel arduino (IRremote et Stepper)

======================================================================================================
									UTILISATION

ATTENTION, l'utilisation de se programme nécessite la modification des scripts .ino. Si vous voulez utiliser se programme vous devez l'adapter en fonction de vôtre situation, car il est configurer pour mon cas personnel en utilisant une télécommande infrarouge qui sera pas forcément la même pour vous. Le nombre de pas des moteurs ainsi que les conditions de sécurités seront différentes pour vous. C'est pour cela qu'il y a un script de test pour adapter vos réglages, un script final qui sera le script que vous devrez téléversser une fois vôtre configuration fini et un script de mesure qui vous servira à mesurer des fréquences infrarouge pour paramétrer votre futur télécommande avec vôtre récepteur infrarouge.

Composant nécessaire:
	1 Arduino uno/nano/mega au choix
	1 Récepteur infrarouge
	1 Télécommande infrarouge
	  Des Moteurs pas a pas (je vous laisse le choix)
	1 Breadboard
	  Des câbles

Pour utiliser se script vous devez modifier les valeurs de nombre de pas des moteurs ainsi que les valeurs infrarouge.