#pragma once

#include <Arduino.h>

//#define DEBUG

#define VREF_5V 4.82
#define VREF 3.365

#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"
#define WIFI_AP_PASSWORD "password"

#define MQTT_SERVER "mqtt_server"
#define MQTT_PORT 1883

#define NTP_SERVER "a.st1.ntp.br"
#define NTP_PORT 123
#define NTP_LOCALPORT 2390
#define NTP_INTERVAL 60 *10 * 1000 // Every 10 minutes.

#define ALARM_LED_PIN D4

#define SENSOR_DHT_PIN D1
#define SENSOR_DHT_READ_INTERVAL 60 * 1000 // Every minute.
#define SENSOR_DHTTYPE DHT11

#define SENSOR_ULTRASONIC_TRIGGER_PIN D7
#define SENSOR_ULTRASONIC_ECHO_PIN D8
#define SENSOR_ULTRASONIC_READ_INTERVAL 1000 // Every second.

#define SENSOR_MPXH6300A_PIN A0
#define SENSOR_MPXH6300A_READ_INTERVAL 1000 // Every second.

