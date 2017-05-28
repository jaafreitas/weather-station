#pragma once

#include <Arduino.h>

void setupDebug();

void debugMsg(bool printtime, const char* format, ...);

