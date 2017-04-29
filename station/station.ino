#include <ESP8266WiFi.h>
#include "settings.h"
#include "conn.h"
#include "alarm.h"

Conn* conn;
char stationID[10];

void setup() {
  Serial.begin(115200);

  sprintf(stationID, "%d", ESP.getChipId());
  
  setupAlarm();  
  conn = new Conn(stationID);
}

void loop() {
  conn->loop();
}

