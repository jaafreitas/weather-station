#include <Esp.h>
#include "settings.h"
#include "debug.h"
#include "version.h"
#include "conn.h"
#include "alarm.h"
#include "ntp.h"
#include "ota.h"
#include "sensorDHT.h"
#include "sensorUltrasonic.h"
#include "sensorMPXH6300A.h"

Conn* conn;
String stationID;

void setup() {
  setupDebug();

  debugMsg(false, "\n***** %s *****\n", title());
  
  stationID = String(ESP.getChipId());
  
  setupAlarm();
  conn = new Conn(stationID);
  setupNTPClient();
  setupOTA();

  setupSensorDHT();
  setupSensorUltrasonic();
  setupSensorMPXH6300A();
}

void loop() {
  conn->loop();
  loopOTA();
  
  loopSensorDHT([](String sensor, float value) {
    conn->notify(sensor, value);
  });
  
  loopSensorUltrasonic([](String sensor, float value) {
    conn->notify(sensor, value);
  });

  loopSensorMPXH6300A([](String sensor, float value) {
    conn->notify(sensor, value);
  });
}

