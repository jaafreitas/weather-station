#include <ESP8266WiFi.h>
#include "settings.h"
#include "debug.h"
#include "alarm.h"
#include "conn.h"
#include "version.h"

WiFiClient wifiClient;

extern String uptime;

void setupWiFi(const char* _stationID) {
  debugMsg(false, "Starting WiFi Setup...\n", _stationID);
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();

  WiFi.softAP(_stationID, WIFI_AP_PASSWORD);
  debugMsg(false, "Access Point %s started at IP address %s\n", _stationID, WiFi.softAPIP().toString().c_str());
    
  debugMsg(false, "Connecting station %s to SSID %s", _stationID, WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    debugMsg(false, ".");
  }
  debugMsg(false, " Ok.\n");
  
  debugMsg(false, "IP address: %s\n", WiFi.localIP().toString().c_str());
}

void callbackMQTT(char* topic, byte* payload, unsigned int length) {
  char c_payload[length];
  memcpy(c_payload, payload, length);
  c_payload[length] = '\0';

  debugMsg(true, "<- %s: %s\n", topic, c_payload);

  if (String(topic).endsWith("alarm")) {
    alarm(String(c_payload).toInt());
  }
}

Conn::Conn(String stationID) {
  this->_stationID = stationID;

  setupWiFi(this->_stationID.c_str());
  
  this->_PubSubClient = new PubSubClient(wifiClient);
  this->_PubSubClient->setServer(MQTT_SERVER, MQTT_PORT);
  this->_PubSubClient->setCallback(callbackMQTT);
}

void Conn::connect() {
  if (!this->_PubSubClient->connected()) {
    while (!this->_PubSubClient->connected()) {
      debugMsg(true, "Attempting MQTT connection on %s...", MQTT_SERVER);
      if (this->_PubSubClient->connect(this->_stationID.c_str())) {
        debugMsg(false, " Ok.\n");
  
        // Once connected, publish announcements...
        notify("version", version, true);
        if (uptime.length() > 0) {
          notify("uptime", uptime, true);
        }

        // ... and resubscribe
        listen("alarm");
      } else {
        debugMsg(false, " ERROR: %d. Trying again in 10 seconds.\n", this->_PubSubClient->state());
        delay(10000);
      }
    }
  }
};

void Conn::loop() {
  this->connect();
  this->_PubSubClient->loop();
}

String Conn::fullTopic(String topic) {
  return "station/" + this->_stationID + "/" + topic;
}

void Conn::notify(String topic, String payload, bool retained) {
  debugMsg(true, "-> %s: %s\n", fullTopic(topic).c_str(), payload.c_str());
  this->_PubSubClient->publish(fullTopic(topic).c_str(), payload.c_str());
}

void Conn::notify(String sensor, float value) {
  static char payload[5];
  dtostrf(value, 5, 2, payload);

  notify("sensor/" + sensor, String(payload), false);  
}

void Conn::listen(String topic) {
  debugMsg(true, "++ %s\n", fullTopic(topic).c_str());
  this->_PubSubClient->subscribe(fullTopic(topic).c_str());
}

