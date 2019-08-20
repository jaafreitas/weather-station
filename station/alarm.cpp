#include "alarm.h"
#include "settings.h"

void setupAlarm() {
  pinMode(ALARM_PIN, OUTPUT);
  digitalWrite(ALARM_PIN, LOW);

  pinMode(STATUS_PIN, OUTPUT);
  // HIGH means OFF on ESP-12E.
  digitalWrite(STATUS_PIN, HIGH);
}

void alarm(bool value) {
  digitalWrite(ALARM_PIN, value);
}
