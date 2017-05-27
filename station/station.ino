#include <Esp.h>
#include "settings.h"
#include "conn.h"
#include "alarm.h"
#include "ntp.h"
#include "sensorDHT.h"
#include "sensorUltrasonic.h"
#include "sensorMPXH6300A.h"

Conn* conn;
char stationID[10];

void setup() {
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  
  sprintf(stationID, "%d", ESP.getChipId());
  
  setupAlarm();
  conn = new Conn(stationID);
  setupNTPClient();

  setupSensorDHT();
  setupSensorUltrasonic();
  setupSensorMPXH6300A();
}

void loop() {
  conn->loop();
  
  loopSensorDHT([](const char* sensor, float value) {
    conn->notify(sensor, value);
  });
  
  loopSensorUltrasonic([](const char* sensor, float value) {
    conn->notify(sensor, value);
  });

  loopSensorMPXH6300A([](const char* sensor, float value) {
    conn->notify(sensor, value);
  });
}

