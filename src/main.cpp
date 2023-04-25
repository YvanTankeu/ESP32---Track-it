/*
  Titre      : Connect to wifi
  Auteur     : Yvan Tankeu
  Date       : 01/03/2023
  Description: Faire connecter son esp32 a un wifi
  Version    : 0.0.1
*/

#ifndef __ARDUINO_H__ // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
#include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif
#include "capteurGps.hpp"
#include "capteurChoc.hpp"
#include "moteur.hpp"
#include "led.hpp"
#ifndef __CONNECT_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
#include <connect.hpp> // Si elle n'est pas incluse, l'inclut
#endif
#include <WiFiManager.h>
#include <PubSubClient.h>

#define gpsSerial Serial1

// RGB LED
const u_int16_t redLED = 21;   // red LED connects to digital pin 21
const u_int16_t greenLED = 18; // green LED connects to digital pin 18
const u_int16_t blueLED = 19;  // blue LED connects to digital pin 19

// Moteur
const u_int16_t moteurPin = 23;

const u_int16_t capteurChocPin = 22;

const char *mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

// char BROKER[] = "test.mosquitto.org";
//  char BROKER[] = "192.168.1.98";
char BROKER[] = "192.168.2.32";
// char BROKER[] = "192.168.2.50";
uint16_t port = 1883;

CapteurGps gpsSensor(1);
Moteur moteur(1, moteurPin);
CapteurChoc choc(1, capteurChocPin);
LED ledRGB(1, redLED, greenLED, blueLED);

Connect conn;
// WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
WiFiManager wm;

std::pair<double, double> geo;

double speed;
double longitude;
double latitude;
double acceleration;

u_int8_t valMoteur;
int prevData;

bool rpcData;
bool lastRpcValue = false;
bool estDemarre = true;

void gestionLumieres()
{
    if (speed > 105)
    {
        ledRGB.startLight(ledRGB.ROUGE);
    }
    else if (speed > 90 && speed < 100)
    {
        ledRGB.startLight(ledRGB.BLEU);
    }
    else
    {
        ledRGB.startLight(ledRGB.VERT);
    }
}

void blinkLedd()
{
    // Allumer et éteindre la LED 3 fois rapidement
    for (int i = 0; i < 3; i++)
    {
        ledRGB.startLight(ledRGB.VERT);
        delay(100);
        ledRGB.arreter();
        delay(100);
    }
}

void blinkLed(int numBlinks, int onTime, int offTime)
{
    for (int i = 0; i < numBlinks; i++)
    {
        ledRGB.startLight(ledRGB.VERT);
        ledRGB.arreter();
        delay(offTime);
    }
}

void handleRpcData()
{

    rpcData = conn.getBtnStatus();
    //Serial.print(rpcData);
    // Vérifier si la valeur RPC a changé
    if ((rpcData) && !lastRpcValue)
    {
        moteur.demarrer();
        Serial.println("Moteur en marche....");
        lastRpcValue = true;
        estDemarre = true;
    }
    else if ((!rpcData) && lastRpcValue)
    {
        moteur.arreter();
        Serial.println("Moteur en arret....");
        lastRpcValue = false;
        estDemarre = false;
        ledRGB.arreter();
    }
    else
    {
        // La valeur RPC n'a pas changé
        // Ne rien faire
    }
}

void obtenirDonneesGPS()
{
    // Obtenir les données de géolocalisation
    auto geo = gpsSensor.getGeolocalisation();
    latitude = geo.first;
    longitude = geo.second;

    // Obtenir la vitesse et l'accélération
    speed = gpsSensor.vitesse();
    acceleration = gpsSensor.getAcceleration();

    // Obtenir la valeur du moteur
    valMoteur = digitalRead(moteur.pinMoteur());
}

void appendSend()
{
    int wifiStatus = (WiFi.status() == WL_CONNECTED) ? 1 : 0;
    Serial.println(wifiStatus);
    int brokerStatus = (conn.brokerConnected()) ? 1 : 0;

    conn.appendTimestamps(random(100000, 120000));
    conn.appendPayload("Longitude", longitude);
    conn.appendPayload("Latitude", latitude);
    conn.appendPayload("Vitesse", speed);
    conn.appendPayload("Acceleration", acceleration);
    conn.appendPayload("Moteur", valMoteur);
    conn.appendPayload("Choc", choc.detecterChoc());
    conn.appendPayload("WiFi", wifiStatus);
    conn.appendPayload("Broker", brokerStatus);

    conn.envoyerData();
}
void sample()
{
    double latitudes[] = {47.712559, 47.712559, 47.712559, 47.712555, 47.712551, 47.712551, 47.712543, 47.712543, 47.712543, 47.712543, 47.712543, 47.712547, 47.712547, 47.712547, 47.712559, 47.712509, 47.711994, 47.711292, 47.710911, 47.710625, 47.710247, 47.709839, 47.70945, 47.709019, 47.708485, 47.70792, 47.707451, 47.707054, 47.706421, 47.705795, 47.70507, 47.704475, 47.703617, 47.70232, 47.645962, 47.645512, 47.645172, 47.645218, 47.645443, 47.645981, 47.647011, 47.679523, 47.705101, 47.706348, 47.707458, 47.707954, 47.708122, 47.708508, 47.708961, 47.709351, 47.709709, 47.710121, 47.710541, 47.710842, 47.710953, 47.711113, 47.711803, 47.712437};
    double longitudes[] = {-65.706551, -65.706551, -65.706551, -65.706543, -65.706543, -65.706551, -65.706551, -65.706551, -65.706551, -65.706551, -65.706558, -65.706573, -65.706573, -65.706573, -65.70649, -65.706421, -65.706268, -65.706108, -65.706482, -65.707703, -65.709282, -65.711006, -65.712646, -65.714363, -65.716202, -65.717812, -65.719002, -65.719322, -65.718475, -65.717194, -65.716194, -65.715614, -65.71479, -65.713593, -65.699287, -65.699425, -65.700211, -65.701241, -65.702072, -65.702347, -65.702248, -65.700638, -65.716026, -65.71666, -65.71701, -65.717293, -65.71714, -65.716026, -65.71447, -65.712914, -65.711357, -65.709625, -65.707909, -65.706635, -65.706154, -65.705963, -65.706108, -65.706268};
    double vitesses[] = {0.02, 0.02, 0.04, 0.04, 0.07, 0.02, 0.06, 0.13, 0.07, 0.02, 0.61, 0.15, 0.09, 0.17, 5.06, 15.41, 38.08, 36.39, 36.97, 59.15, 69.64, 69.64, 65.86, 75.1, 76.3, 63.28, 42.93, 33.85, 56.62, 62.84, 51.69, 35.5, 76.23, 94.54, 21.63, 35.1, 38.84, 38.84, 34.76, 38.35, 74.82, 99.88, 86.49, 71.6, 52.54, 7.82, 26.26, 61.15, 66.76, 61.86, 66.67, 72.75, 66.93, 40.26, 1.87, 24.45, 46.36, 19.58};

    unsigned long tempsDernierEnvoi = 0;
    unsigned long intervalleEnvoi = 5000; // 2 secondes

    int i = 0;
    // Obtenir la valeur du moteur
    valMoteur = digitalRead(moteurPin);
    
    while (i < 50)
    {
        conn.receiveData();
        handleRpcData(); // Traitement de la requête
        int wifiStatus = (WiFi.status() == WL_CONNECTED) ? 1 : 0;
        int brokerStatus = (conn.brokerConnected()) ? 1 : 0;
        conn.appendTimestamps(1000000);
        conn.appendPayload("Longitude", longitudes[i]);
        conn.appendPayload("Latitude", latitudes[i]);
        conn.appendPayload("Vitesse", vitesses[i]);
        conn.appendPayload("Acceleration", acceleration);
        conn.appendPayload("Moteur", rpcData);
        conn.appendPayload("Choc", choc.detecterChoc());
        conn.appendPayload("WiFi", wifiStatus);
        conn.appendPayload("Broker", brokerStatus);

        // Vérifier si suffisamment de temps s'est écoulé depuis le dernier envoi
        if (millis() - tempsDernierEnvoi >= intervalleEnvoi)
        {
            conn.envoyerData();
            ledRGB.blink(100, ledRGB.BLEU);

            // Mettre à jour le temps du dernier envoi
            tempsDernierEnvoi = millis();
            i++; // Passer à la prochaine donnée à envoyer
        }
    }
}

void initProgram()
{
    // Serial.begin(9600);
    gpsSerial.begin(9600);
    conn.connectToBroker(BROKER, port);
    // Serial.println("Bracnhez au test mosquitto");
    moteur.demarrer();
}

void setup()
{
    // initProgram();
    // WiFi.mode(WIFI_STA); //définit explicitement le mode, esp par défaut à STA + AP
    // c'est une bonne pratique de s'assurer que votre code définit le mode wifi comme vous le souhaitez.

    // placez votre code d'installation ici, à exécuter une fois :
    Serial.begin(9600);

    //wm.resetSettings();
    wm.setTitle("Configuration de la connectivité Track-It");

    bool res;
    // res = wm.autoConnect(); //nom AP généré automatiquement à partir de chipid
    // res = wm.autoConnect("AutoConnectAP"); //ap anonyme
    res = wm.autoConnect("GPSWIFI", "12345678"); // application protégée par mot de passe

    if (!res)
    {
        Serial.println("Échec de connexion");
        // ESP.restart();
    }
    else
    {
        // si vous arrivez ici, vous êtes connecté au WiFi
        Serial.println("connected...yeey :)");
    }

    pinMode(LED_BUILTIN, OUTPUT);
    conn.connectToBroker(BROKER, port);
}

void loop()
{   
    //conn.receiveData();

    // Traiter requete rpc
    handleRpcData();

    //  si le moteur est démarré ou pas on allumera des light en fonction de cette information
    // Gérer les LEDs
    if (estDemarre)
    {
        gestionLumieres();
    }

    // obtenirDonneesGPS();
    sample();
}
