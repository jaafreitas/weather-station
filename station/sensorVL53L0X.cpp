#include "src/Adafruit_VL53L0X/Adafruit_VL53L0X.h"
#include "sensorVL53L0X.h"
#include "settings.h"

extern "C" {
#include "user_interface.h"
}

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

os_timer_t sensorVL53L0XTimer;

bool canReadSensorVL53L0X = false;

void sensorVL53L0XRead(void *parg) {
  canReadSensorVL53L0X = true;
}

void setupSensorVL53L0X() {
  if (!lox.begin()) {  
    Serial.println("VL53L0X sensor not connected!");
  } else {
    canReadSensorVL53L0X = true;
    os_timer_disarm(&sensorVL53L0XTimer);
    os_timer_setfn(&sensorVL53L0XTimer, sensorVL53L0XRead, NULL);
    os_timer_arm(&sensorVL53L0XTimer, SENSOR_VL53L0X_READ_INTERVAL, true);
  }
}

void loopSensorVL53L0X(Conn* conn) {
  if (canReadSensorVL53L0X) {
    canReadSensorVL53L0X = false;

    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4) {
      conn->notify_sensor("VL53L0X/distance", (measure.RangeMilliMeter/10.0));
    }    
  }
}
