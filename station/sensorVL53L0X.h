#pragma once

#include <Arduino.h>
#include "conn.h"

void setupSensorVL53L0X();

void loopSensorVL53L0X(Conn* conn);
