#ifndef LIDAR_H
#define LIDAR_H
#include <Arduino.h>
#include "RPLidar.h"

extern float distance;
extern float angle;
extern bool startBit;
extern byte quality;

void LidarInit();
void LidarGetData();
void LidarStop();
float LidarGetDistanceFromeScaneAngle(float minAngle, float maxAngle);

#endif
