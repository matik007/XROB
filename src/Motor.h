#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "Lidar.h"

void MotorInit();

void MotorStop();

void MotorForward(uint8_t sp = 200);
void MotorForwardLidar(uint8_t minAngle = 240, uint8_t maxAngle = 300);

void MotorBack(uint8_t sp = 230);

#endif
