#pragma once

#include <Arduino.h>
#include "conn.h"

void setupSensorBMP280();

void loopSensorBMP280( CONN_NOTIFY_SENSOR );

