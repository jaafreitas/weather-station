#pragma once

#include <Arduino.h>
#include "conn.h"

void setupSensorBMP280();

void loopSensorBMP280(Conn* conn);
