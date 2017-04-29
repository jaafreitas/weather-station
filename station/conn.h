#pragma once

#include <Arduino.h>
#include <PubSubClient.h>

class Conn {
  public:
    Conn(char* stationID);
    void loop();
  private:
    char* _stationID;
    PubSubClient* _PubSubClient;
    void connect();
};

