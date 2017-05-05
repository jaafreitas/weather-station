#pragma once

#include <Arduino.h>
#include <PubSubClient.h>

#define CONN_NOTIFY void (*notify)(const char*, float)

class Conn {
  public:
    Conn(char* stationID);
    void loop();
    void notify(const char* sensor, float value);
  private:
    char* _stationID;
    PubSubClient* _PubSubClient;
    void connect();
};

