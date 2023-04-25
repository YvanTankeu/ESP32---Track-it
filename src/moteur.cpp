#ifndef __ARDUINO_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif 

#include "moteur.hpp"

// Constructeurs
Moteur::Moteur() : idMoteur_(0) {}
Moteur::Moteur(int idMoteur, int pinMoteur) : idMoteur_(idMoteur), pinMoteur_(pinMoteur) {
     pinMode(pinMoteur, OUTPUT);
}

// Méthodes de l'interface Actionneur redéfinies
void Moteur::demarrer() {
// Code pour démarrer le moteur
    digitalWrite(pinMoteur_, HIGH);
}

void Moteur::arreter() {
// Code pour arrêter le moteur
    digitalWrite(pinMoteur_, LOW);
}

// Accesseurs et Mutateurs
int Moteur::idMoteur() const {
return idMoteur_;
}

int Moteur::pinMoteur() const{
    return pinMoteur_;
}

void Moteur::idMoteur(int idMoteur) {
    idMoteur_ = idMoteur;
}

void Moteur::pinMoteur(int pinMoteur) {
    pinMoteur_ = pinMoteur;
}