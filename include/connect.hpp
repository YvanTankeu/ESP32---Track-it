#ifndef __CONNECT_HPP__  // Début de la directive de préprocesseur "ifndef", qui évite les inclusions multiples du fichier d'en-tête "Connect.hpp"
#define __CONNECT_HPP__  // Définition du symbole "__CONNECT_HPP__"
#ifndef __WIFI101_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <WiFi.h>  // Si elle n'est pas incluse, l'inclut
#endif 
#include <PubSubClient.h>

class Connect
{
    // Propriétés privées de la classe Connect
    private:
        bool wifiConnected_;
        bool brokerConnected_;
        bool btnStatus_;
        char *host_;
        uint16_t port_;

    // Méthodes publiques de la classe Connect
    public:
        // Constructeur par défaut
        Connect();


        bool wifiConnected() const;
        bool brokerConnected() const;
        bool getBtnStatus() const;

        /**
         * @brief Méthode pour se connecter au broker MQTT en utilisant les identifiants fournis
         * @param host Le nom du broker MQTT
         * @param port Le numéro de port sur lequel se connecter
         */
        void connectToBroker(char *host, uint16_t port);

        void appendPayload(String Name, float Val);

        void appendTimestamps(float value);
        
        void receiveData();

         void callback (char* topicRpcCallback, byte* payload, unsigned int length);

        void envoyerData();

        
};

#endif // Fin de la directive de préprocesseur "ifndef", avec la définition du symbole "__CONNECT_HPP__"