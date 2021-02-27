
#ifndef PID_H
#define PID_H

#include <Arduino.h>

int computePID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut);

#endif
