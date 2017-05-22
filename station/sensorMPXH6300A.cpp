#include "sensorMPXH6300A.h"
#include "settings.h"

extern "C" {
#include "user_interface.h"
}

os_timer_t sensorMPXH6300ATimer;

bool canReadSensorMPXH6300A = true;

void sensorMPXH6300ARead(void *parg) {
  canReadSensorMPXH6300A = true;
}

void setupSensorMPXH6300A() {
  pinMode(SENSOR_MPXH6300A_PIN, INPUT);
  
  os_timer_disarm(&sensorMPXH6300ATimer);
  os_timer_setfn(&sensorMPXH6300ATimer, sensorMPXH6300ARead, NULL);
  os_timer_arm(&sensorMPXH6300ATimer, SENSOR_MPXH6300A_READ_INTERVAL, true);
}

void loopSensorMPXH6300A( CONN_NOTIFY  ) {
  if (canReadSensorMPXH6300A) {
    canReadSensorMPXH6300A = false;

    int sensorValue = analogRead(SENSOR_MPXH6300A_PIN);
    float volts = (sensorValue / 1023.0) * VREF;
    float kPa = (volts + 0.00353 * VREF_5V) / (0.00318 * VREF_5V);
    float atm = kPa / 101.325;
   
    notify("MPXH6300A", atm);
  }
}
