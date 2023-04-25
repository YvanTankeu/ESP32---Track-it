#ifndef __MOTEUR_HPP__
#define __MOTEUR_HPP__

#include "actionneur.hpp"

class Moteur : public Actionneur {
    private:
        int idMoteur_;// Identifiant unique du moteur
        int pinMoteur_;
    public:
        // Constructeurs
        Moteur();
        Moteur(int idMoteur, int pinMoteur);

        // Méthodes de l'interface Actionneur redéfinies
        virtual void demarrer() override;
        virtual void arreter() override;
    
        // Accesseurs et Mutateurs
        int idMoteur() const;
        int pinMoteur() const;

        void idMoteur(int idMoteur);
        void pinMoteur(int pinMoteur);
    };

#endif // __MOTEUR_HPP__
