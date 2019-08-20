#include "sensorUltrasonic.h"
#include "settings.h"

extern "C" {
#include "user_interface.h"
}

// The "Pace of Sound" at 20 Celsius degrees is 29.1
#define PACE_OF_SOUND 29.1

// HC-SR04 min range in cm
#define MIN_RANGE 2
// HC-SR04 max range in cm
#define MAX_RANGE 400

#define MIN_DURATION MIN_RANGE * PACE_OF_SOUND * 2
#define MAX_DURATION MAX_RANGE * PACE_OF_SOUND * 2

os_timer_t sensorUltrasonicTimer;

bool canReadSensorUltrasonic = true;

void sensorUltrasonicRead(void *parg) {
  canReadSensorUltrasonic = true;
}

void setupSensorUltrasonic() {
  pinMode(SENSOR_ULTRASONIC_TRIGGER_PIN, OUTPUT);
  pinMode(SENSOR_ULTRASONIC_ECHO_PIN, INPUT);

  os_timer_disarm(&sensorUltrasonicTimer);
  os_timer_setfn(&sensorUltrasonicTimer, sensorUltrasonicRead, NULL);
  os_timer_arm(&sensorUltrasonicTimer, SENSOR_ULTRASONIC_READ_INTERVAL, true);
}

void loopSensorUltrasonic(Conn* conn) {
  if (canReadSensorUltrasonic) {
    canReadSensorUltrasonic = false;

    long duration;
    float distance;

    digitalWrite(SENSOR_ULTRASONIC_TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(SENSOR_ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENSOR_ULTRASONIC_TRIGGER_PIN, LOW);
    duration = pulseIn(SENSOR_ULTRASONIC_ECHO_PIN, HIGH, MAX_DURATION);

    // The duration is close to zero when we have a timeout.
    if (duration < MIN_DURATION) {
      duration = MAX_DURATION;
    }

    distance = (duration / 2) / PACE_OF_SOUND;

    if ((distance > MIN_RANGE) && (distance < MAX_RANGE)) {
      conn->notify_sensor("HC-SR04/distance", distance);
    }
  }
}
