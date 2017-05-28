#include <TimeLib.h>
#include "debug.h"
#include "settings.h"
#include "ntp.h"

void setupDebug() {
#ifdef DEBUG
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
#endif
}

void debugMsg(bool printtime, const char* format, ...) {
#ifdef DEBUG
  if (printtime) {
    Serial.print(getISOTime() + " ");
  }

  char str[200];

  va_list args;
  va_start(args, format);

  vsnprintf(str, sizeof(str), format, args);
  Serial.print(str);

  va_end(args);
#endif
}

