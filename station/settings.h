#pragma once

#include <Arduino.h>

#define DEBUG

#define VREF_5V 4.78
#define VREF 3.28

static const char* STATION_PREFIX = "";

static const char* WIFI_SSID = "ssid";
static const char* WIFI_PASSWORD = "password";
static const char* WIFI_AP_PASSWORD = "password";
static const uint8_t WIFI_CONNECTION_RETRIES = 20;

static const unsigned long MQTT_CONNECTION_RETRY = 60000;

static const char* MQTT_SERVER = "mqtt_server";
static const uint16_t MQTT_PORT = 1883;
static const char* MQTT_USER = "";
static const char* MQTT_PASSWORD = "";
static const char* MQTT_TOPIC_PREFIX = "";

static const char* NTP_SERVER = "ntp_server";
static const uint16_t NTP_PORT = 123;
static const uint16_t NTP_LOCALPORT = 2390;
static const unsigned long NTP_INTERVAL = 1 * 60 * 60 * 1000; // Every 1 hour (in milliseconds)
static const unsigned long TZ_OFFSET = (-3 * 60 * 60); // in seconds.

static const uint8_t ALARM_PIN = D5;
static const uint8_t STATUS_PIN = D4; // LED_BUILTIN

static const uint8_t SENSOR_BMP280_SCK_PIN = D1;
static const uint8_t SENSOR_BMP280_SDI_PIN = D2;
static const unsigned long SENSOR_BMP280_READ_INTERVAL = 1000; // Every second.

static const uint8_t SENSOR_DHT_PIN = D3;
static const unsigned long SENSOR_DHT_READ_INTERVAL = 60 * 1000; // Every minute.
#define SENSOR_DHTTYPE DHT11

static const uint8_t SENSOR_ULTRASONIC_TRIGGER_PIN = D7;
static const uint8_t SENSOR_ULTRASONIC_ECHO_PIN = D8;
static const unsigned long SENSOR_ULTRASONIC_READ_INTERVAL = 1000; // Every second.

static const uint8_t SENSOR_MPXH6300A_PIN = A0;
static const unsigned long SENSOR_MPXH6300A_READ_INTERVAL = 1000; // Every second.
