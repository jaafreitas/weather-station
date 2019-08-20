#pragma once

#include <Arduino.h>
#include "conn.h"

void setupNTPClient();

void loopNTPClient(Conn* conn);

String getISOTime();
