#ifndef MYI2C_H
#define MYI2C_H

#include <Arduino.h>
#include <Wire.h>
#include "Motor.h"
#include "Lidar.h"

#define STOP 0
#define AUTO_CONTROL 1
#define MANUAL_CONTROL 2

extern uint8_t STATE;

void MyI2CInit();

void receiveEvent();

#endif
