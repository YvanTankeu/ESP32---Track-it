#ifndef __CAPTEUR_HPP__
#define __CAPTEUR_HPP__

#include <string>

class Capteur {
    private:
        std::string idCapteur_; // Identifiant unique du capteur
        std::string typeCapteur_; // Type de capteur (GPS, capteur de choc, etc.)
    public:
        // Méthode pour obtenir l'identifiant du capteur
        const std::string& idCapteur() const;
        
        // Méthode abstraite pour obtenir les données du capteur
        virtual double getData() = 0;

        // Accesseurs et Mutateurs
        const std::string& typeCapteur() const;
        void typeCapteur(const std::string& typeCapteur);
    };

#endif //__CAPTEUR_HPP__