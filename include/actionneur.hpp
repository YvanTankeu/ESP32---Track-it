#ifndef __ACTIONNEUR_HPP__  // Début de la directive de préprocesseur "ifndef", qui évite les inclusions multiples du fichier d'en-tête "actionneur.hpp"
#define __ACTIONNEUR_HPP__  // Définition du symbole "__ACTIONNEUR_HPP__"

class Actionneur {
public:
  virtual void demarrer() = 0; // méthode virtuelle pure pour démarrer l'actionneur
  virtual void arreter() = 0; // méthode virtuelle pure pour arrêter l'actionneur
};

#endif // Fin de la directive de préprocesseur "ifndef", avec la définition du symbole "__ACTIONNEUR_HPP__"
