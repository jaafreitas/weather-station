#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ssid";
const char* password = "password";
#define LED_BUILTIN 2

const char* mqtt_server = "mqtt_server";

char stationID[10];

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  // HIGH means OFF on ESP-12E.
  digitalWrite(LED_BUILTIN, HIGH);
  
  sprintf(stationID, "%d", ESP.getChipId());

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(mqtt_callback);
  mqtt_connect();
}

void setup_wifi() {
  Serial.printf("\nConnecting station %s to SSID %s", stationID, ssid);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Ok.");
  
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
}

void mqtt_connect() {
  while (!client.connected()) {
    Serial.printf("Attempting MQTT connection on %s...", mqtt_server);
    if (client.connect(stationID)) {
      Serial.println(" Ok.");

      // Once connected, publish an announcement...
      char msg[100];
      sprintf(msg, "station/%s/status", stationID);
      client.publish(msg, "on");

      // ... and resubscribe
      sprintf(msg, "station/%s/alarm", stationID);
      client.subscribe(msg);      
    } else {
      Serial.printf(" error: %s. Trying again in 10 seconds.\n", client.state());
      delay(10000);
    }
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  char c_payload[length];
  memcpy(c_payload, payload, length);
  c_payload[length] = '\0';
  
  Serial.printf("<- %s: %s\n", topic, c_payload);
  
  if (String(topic).endsWith("alarm")) {
    alarm(String(c_payload).toInt());
  }
}

void alarm(bool value) {  
  digitalWrite(LED_BUILTIN, !value);
}

void loop() {
  if (!client.connected()) {
    mqtt_connect();
  }
  client.loop();
}

