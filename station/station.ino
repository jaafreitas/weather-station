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
#include "sensorBMP280.h"
#include "sensorVL53L0X.h"

Conn* conn;
String stationID;

void setup() {
  setupDebug();

  stationID = String(STATION_PREFIX) + String(ESP.getChipId());

  debugMsg("\n***** %s *****\n", title(stationID));
  
  setupAlarm();
  conn = new Conn(stationID);
  setupNTPClient();
  setupOTA();

  setupSensorDHT();
  setupSensorUltrasonic();
  setupSensorMPXH6300A();
  setupSensorBMP280();
  setupSensorVL53L0X();
}

void loop() {
  conn->loop();
  
  loopOTA();
  
  loopNTPClient(conn);
  loopSensorDHT(conn);  
  loopSensorUltrasonic(conn);
  loopSensorMPXH6300A(conn);
  loopSensorBMP280(conn);
  loopSensorVL53L0X(conn);
}
