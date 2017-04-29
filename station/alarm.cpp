#include "alarm.h"
#include "settings.h"

void setupAlarm() {
  pinMode(PIN_LED_ALARM, OUTPUT);
  // HIGH means OFF on ESP-12E.
  digitalWrite(PIN_LED_ALARM, HIGH);  
}

void alarm(bool value) {
  digitalWrite(PIN_LED_ALARM, !value);
}

