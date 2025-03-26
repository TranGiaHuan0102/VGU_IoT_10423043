#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>
#include "config.h"

void connectWiFi()  // Function to connect to WiFi
{
    Serial.println("Connecting to WiFi...");

    WiFi.disconnect(true);  // Ensure previous connections are cleared
    delay(1000);

    WiFi.begin(SSID, PASSWORD);  // Start WiFi connection

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {  // Retry for 20 seconds
        Serial.print(".");
        delay(1000);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to WiFi!");
        // If you want to check your IP address, uncomment this code
        /*
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        */        
    } else {
        Serial.println("\nFailed to connect. Check WiFi settings.");
    }
}

WiFiClient espClient;         // Create a WiFi client for ESP32
PubSubClient client(espClient); // Create an MQTT client using WiFi
void reconnectMQTTClient()
{
    /* Checks if the MQTT client is connected*/
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        /*Attempts to connect to the MQTT broker.
        Uses client.connect() to connect using CLIENT_NAME.
        CLIENT_NAME.c_str() converts CLIENT_NAME (a string) into a const char*, which connect() expects.*/
        if (client.connect(CLIENT_NAME.c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("Retying in 5 seconds - failed, rc=");
            Serial.println(client.state());
            
            delay(5000);
        }
    }
}

void createMQTTClient()
{
    /*BROKER.c_str() → Converts BROKER (a std::string) to const char*, which setServer() requires.
    1883 → The default port for MQTT communication.*/
    client.setServer(BROKER.c_str(), 1883);
    
    /*Calls reconnectMQTTClient(), which tries to establish a connection to the MQTT broker.*/
    reconnectMQTTClient();
}

#define LED_PIN 5  // GPIO5 (D5)
void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600); // Start Serial Monitor
    connectWiFi();  // Call function to connect to WiFi
    createMQTTClient();
}

void loop()
{
    // Reconnect to the MQTT Broker if Disconnected
    reconnectMQTTClient();
    // Process MQTT Messages
    client.loop();
    delay(2000);
}