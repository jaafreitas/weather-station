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
char stationID[10];

void setup() {
  setupDebug();

  debugMsg(false, "\n***** Station %s (%s, %s) [ESP Core %s (WeMos D1 mini)] *****\n", version, __DATE__, __TIME__, ESP.getCoreVersion().c_str());

  sprintf(stationID, "%d", ESP.getChipId());

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

