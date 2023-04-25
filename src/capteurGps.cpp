// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions du capteur gps ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include "capteurGps.hpp"
#include <Arduino.h>
#include <TinyGPS++.h>

#define gpsSerial Serial1

// L'objet TinyGPSPlus
TinyGPSPlus gps;

// Constructeurs
CapteurGps::CapteurGps() : Capteur(), idCapteurGps_(0), latitude_(0.0), longitude_(0.0), vitesse_(0.0) {}

CapteurGps::CapteurGps(int idCapteurGps) : Capteur(), idCapteurGps_(idCapteurGps), latitude_(0.0), longitude_(0.0), vitesse_(0.0){}

std::pair<double, double> CapteurGps::getGeolocalisation()
{
    // Cette fonction récupère la position actuelle du bus à partir du module GPS
    // Boucle pour lire les données provenant du module GPS
    while (gpsSerial.available() > 0)
    {
         // Si les données sont valides, mise à jour de la position et de la vitesse
        if (gps.encode(gpsSerial.read()))
        {
            // Obtention de la latitude et de la longitude
            latitude_ = gps.location.lat();
            longitude_ = gps.location.lng();

            // Obtention de la vitesse en km/h
            vitesse_ = gps.speed.kmph();
        }
    }
    // Retour de la paire de doubles contenant la latitude et la longitude
    return std::make_pair(latitude_, longitude_);
}

double CapteurGps::getData()
{
    // Récupérer la latitude et la longitude du capteur GPS
    double latitude = getGeolocalisation().first;
    double longitude = getGeolocalisation().second;

    // Calculer la valeur à retourner (par exemple, la somme de la latitude et de la longitude)
    double value = latitude + longitude;

    return value;
}

double CapteurGps::getAcceleration()
{
    // Déclaration des variables pour le timer
    unsigned long tempsDebut = millis(); 
    unsigned long tempsAttente = 1000; 

    // Attendre le temps requis
    while (millis() - tempsDebut < tempsAttente) {}

    // Mesurer la nouvelle vitesse
    double newVitesse = vitesse();

    // Calculer la différence de vitesse et de temps
    double deltaVitesse = newVitesse - vitesse_;
    double deltaTime = (double)tempsAttente / 1000; // temps en secondes

    // Calculer l'accélération
    double acceleration = deltaVitesse / deltaTime;

    return acceleration;
}


// Accesseurs et Mutateurs
int CapteurGps::idCapteurGps() const
{
    return idCapteurGps_;
}

void CapteurGps::idCapteurGps(int idCapteurGps)
{
    idCapteurGps_ = idCapteurGps;
}

double CapteurGps::vitesse() const
{
    return vitesse_;
}

void CapteurGps::vitesse(double vitesse)
{
    vitesse_ = vitesse;
}

double CapteurGps::latitude() const
{
    return latitude_;
}

void CapteurGps::latitude(double latitude)
{
    latitude_ = latitude;
}


double CapteurGps::longitude() const
{
    return longitude_;
}

void CapteurGps::longitude(double longitude)
{
    longitude_ = longitude;
}


