// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions du capteur de choc --------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------
#ifndef __ARDUINO_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif
#include "capteurChoc.hpp"

CapteurChoc::CapteurChoc() : idCapteurChoc_(0), etat_(false) {} // Initialisation des attributs par défaut

CapteurChoc::CapteurChoc(int id) : idCapteurChoc_(id), etat_(false) {} // Initialisation des attributs avec l'identifiant du capteur

CapteurChoc::CapteurChoc(int id, u_int8_t pin) : idCapteurChoc_(id),  pin_(pin) {
    pinMode(pin_, INPUT_PULLDOWN);
}

bool CapteurChoc::detecterChoc() {
    // Variable pour stocker la valeur du capteur
    int valeurCapteur = 0; 
    valeurCapteur =  digitalRead(pin_);
    
     // Lire la valeur du capteur
      // Si un choc est détecté, retourne true, sinon retourne false
    if( valeurCapteur != 0)
        return true; 
    else
        return false;
}

int CapteurChoc::id() const {
    return idCapteurChoc_; // Retourne l'identifiant du capteur
}

void CapteurChoc::setId(int id) {
    idCapteurChoc_ = id; // Modifie l'identifiant du capteur
}

bool CapteurChoc::etat() const {
    return etat_; // Retourne l'état du capteur
}

void CapteurChoc::setEtat(bool etat) {
    etat_ = etat; // Modifie l'état du capteur
}

double CapteurChoc::getData()
{
    double value = 0;

    return value;
}
