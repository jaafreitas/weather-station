#pragma once

#include <Arduino.h>
#include "conn.h"

void setupNTPClient();

void loopNTPClient( CONN_NOTIFY );

String getISOTime();

