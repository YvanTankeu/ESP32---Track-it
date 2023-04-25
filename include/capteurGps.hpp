#ifndef __CAPTEURGPS_HPP__
#define __CAPTEURGPS_HPP__

#include "capteur.hpp"

class CapteurGps : public Capteur {
    private:
        int idCapteurGps_;
        double latitude_;
        double longitude_;
        double vitesse_;
        
    public:
        // Constructeurs
        CapteurGps();
        CapteurGps(int idCapteurGps);

        /**
         * @brief Get the Geolocalisation object
         * 
         * @return  retourne une paire de valeurs de type double, représentant respectivement la latitude et la longitude du capteur GPS. 
         */
        std::pair<double, double> getGeolocalisation();

        double getData();
        
        // Accesseurs et Mutateurs
        int idCapteurGps() const;
        void idCapteurGps(int idCapteurGps);

        double vitesse() const;
        void vitesse(double vitesse);

        double latitude() const;
        void latitude(double latitude);

        double longitude() const;
        void longitude(double longitude);

        double getAcceleration();
};

#endif