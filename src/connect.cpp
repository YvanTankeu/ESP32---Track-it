
// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions de connect ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include "connect.hpp"
//#include <PubSubClient.h>

static WiFiClient wifiClient;
static PubSubClient  mqttClient(wifiClient);

String Payload = "{"; // Chaine de caractère qui contiendra le message envoyer de l'objet vers node-red
bool first = false;

const char topic[] = "trackIt/data";
const char topicRpc[] = "trackIt/rpc";

/**
 * @brief Construit un nouvel objet de la classe Connect.
 *
 * @param nomWifi const char* Pointeur vers la chaîne SSID.
 * @param motDePasse const char* Optionel pointeur vers la chaîne mot de passe compris entre ASCII 32 et 126 (décimal).
 */

Connect::Connect()
 {}

// Fonction de rappel MQTT pour traiter les messages reçus
void Connect::callback(char *topicRpcCallback, byte *payload, unsigned int length)
{
    Serial.print("Message reçu [");
    Serial.print(topicRpc);
    Serial.print("] ");
    if (String(topicRpcCallback) == topicRpc)
    {
        String message = "";    
        for (int i = 0; i < length; i++)
        {   
            Serial.print((char)payload[i]);
            message += (char)payload[i];
        }
        if (message == "true"){
            btnStatus_ = true;
        }
        else if (message == "false"){
            btnStatus_ = false;
        }
    }
    Serial.println();
}

void Connect::connectToBroker(char *host, uint16_t port)
{
    Serial.print("Tentative de connexion au COURTIER MQTT: ");
    Serial.println(host);
    mqttClient.setServer(host, port);
    mqttClient.setCallback(std::bind(&Connect::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


    while (!mqttClient.connected())
    {
        if (mqttClient.connect("", "alice", "admin"))
        {
            Serial.println("Connected to MQTT Broker");
            // Abonnement à un sujet :
            Serial.print("Abonnement au topic : ");
            Serial.println(topic);
            mqttClient.subscribe(topic);
            if (mqttClient.subscribe(topicRpc)) {
                Serial.print("Abonnement au topic : ");
                Serial.println(topicRpc);
                Serial.println();
            } else {
                Serial.println("Subscription failed.");
            }
        
            brokerConnected_ = true;
            Serial.println();
        }
        else
        {
            Serial.print("Failed to connect to MQTT Broker, rc=");
            Serial.println(mqttClient.state());
            brokerConnected_ = false;
            delay(5000);
        }
    }
}

void Connect::envoyerData()
{
    // Ajoute une accolade fermante à la fin de la chaîne de caractères Payload
    Payload += "}";

    // Envoie le message contenant les données au serveur MQTT
    Serial.print("Envoi des donnees au broker MQTT... ");
    if (mqttClient.publish(topic, Payload.c_str()))
        Serial.println("OK");
    else
        Serial.print("Failed to connect to MQTT Broker, rc=");
        Serial.println(mqttClient.state());

    // Réinitialise la chaîne de caractères Payload
    Payload = "{";
}

void Connect::receiveData()
{
    mqttClient.loop();
}

bool Connect::brokerConnected() const
{
    return brokerConnected_;
}

bool Connect::getBtnStatus() const
{
    return btnStatus_;
}

// {"ts":1666778909000,"values":{
void Connect::appendTimestamps(float value)
{
  first = false;
  Payload = "{\"ts\":";
  Payload += value;
  Payload += ",\"values\":{";
}

//"Temperature":23.169,"Humidite":59.411}}
void Connect::appendPayload(String Name, float Val)
{
  if (first)
  {
        Payload += ",";
  }
  Payload += "\"";
  Payload += Name;
  Payload += "\": ";

  // convertir Val en un nombre à virgule flottante
  String ValStr = String(Val, 6);

  // extraire les six chiffres après la virgule
  int dotIndex = ValStr.indexOf('.');
  String ValAfterDot = ValStr.substring(dotIndex + 1);
  while (ValAfterDot.length() < 6)
  {
        ValAfterDot += '0';
  }

  // concaténer le résultat dans Payload
  Payload += ValStr.substring(0, dotIndex + 1);
  Payload += ValAfterDot;

  first = true;
}
