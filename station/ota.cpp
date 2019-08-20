/*
  To upload through terminal you can use: curl -F "image=@station.bin" station.local/firmware
*/

#include "settings.h"
#include "debug.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setupOTA() {
  const char* update_path = "/firmware";

  debugMsg("Starting Over the Air updater at http://%s%s ... ", WiFi.localIP().toString().c_str(), update_path);
  httpUpdater.setup(&httpServer, update_path);
  httpServer.begin();
  debugMsg("Ok.\n");
}

void loopOTA() {
  httpServer.handleClient();
}
