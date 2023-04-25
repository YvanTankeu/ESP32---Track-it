#ifndef __CapteurChoc_HPP__ // Vérifie si la macro __CapteurChoc_HPP__ n'est pas définie
#define __CapteurChoc_HPP__ // Définit la macro __CapteurChoc_HPP__ pour indiquer que ce code a été inclus

#include "capteur.hpp" // Inclusion du fichier d'en-tête Capteur.hpp

class CapteurChoc : public Capteur { // Définition de la classe CapteurChoc qui hérite de la classe Capteur
private:
    int idCapteurChoc_; // Identifiant du capteur de choc
    uint8_t  pin_;
    bool etat_; // État du capteur de choc
public:
    CapteurChoc(); // Constructeur par défaut
    CapteurChoc(int id); // Constructeur prenant en paramètre l'identifiant du capteur
    CapteurChoc(int id, u_int8_t pin); // Constructeur par défaut

    double getData();

    bool detecterChoc(); // Méthode pour détecter un choc
    int id() const; // Méthode pour obtenir l'identifiant du capteur (const pour indiquer que la méthode ne modifie pas l'état de l'objet)
    void setId(int id); // Méthode pour modifier l'identifiant du capteur
    bool etat() const; // Méthode pour obtenir l'état du capteur (const pour indiquer que la méthode ne modifie pas l'état de l'objet)
    void setEtat(bool etat); // Méthode pour modifier l'état du capteur
};

#endif // Fin de la section de garde.
