#include "alarm.h"
#include "settings.h"

void setupAlarm() {
  pinMode(ALARM_LED_PIN, OUTPUT);
  // HIGH means OFF on ESP-12E.
  digitalWrite(ALARM_LED_PIN, HIGH);
}

void alarm(bool value) {
  digitalWrite(ALARM_LED_PIN, !value);
}

