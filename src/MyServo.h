#ifndef MYSERVO_H
#define MYSERVO_H

#include <Arduino.h>
#include <Servo.h>

extern Servo servo;

void MyServoInit();

void MyServoSend(uint16_t data);

#endif
