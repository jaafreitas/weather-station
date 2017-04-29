#include <ESP8266WiFi.h>
#include "settings.h"
#include "alarm.h"
#include "conn.h"

void setupWiFi(char* _stationID) {
  Serial.printf("\nConnecting station %s to SSID %s", _stationID, WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Ok.");
  
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
}

void callbackMQTT(char* topic, byte* payload, unsigned int length) {
  char c_payload[length];
  memcpy(c_payload, payload, length);
  c_payload[length] = '\0';
  
  Serial.printf("<- %s: %s\n", topic, c_payload);

  if (String(topic).endsWith("alarm")) {
    alarm(String(c_payload).toInt());
  }
};

Conn::Conn(char* stationID) {
  this->_stationID = stationID;

  setupWiFi(stationID);
  
  WiFiClient wifiClient;

  this->_PubSubClient = new PubSubClient(wifiClient);
  this->_PubSubClient->setServer(MQTT_SERVER, MQTT_PORT);
  this->_PubSubClient->setCallback(callbackMQTT);
};

void Conn::connect() {
  if (!this->_PubSubClient->connected()) {
    while (!this->_PubSubClient->connected()) {
      Serial.printf("Attempting MQTT connection on %s...", MQTT_SERVER);
      if (this->_PubSubClient->connect(this->_stationID)) {
        Serial.println(" Ok.");
  
        // Once connected, publish an announcement...
        char msg[100];
        sprintf(msg, "station/%s/status", this->_stationID);
        this->_PubSubClient->publish(msg, "on");
  
        // ... and resubscribe
        sprintf(msg, "station/%s/alarm", this->_stationID);
        this->_PubSubClient->subscribe(msg);      
      } else {
        Serial.printf(" ERROR: %d. Trying again in 10 seconds.\n", this->_PubSubClient->state());
        delay(10000);
      }
    }
  }
};

void Conn::loop() {
  if (!this->_PubSubClient->connected()) {
    this->connect();
  }
  this->_PubSubClient->loop();
}

