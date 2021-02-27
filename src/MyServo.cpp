#include "MyServo.h"

Servo servo;

uint8_t servoPin = 8;

void MyServoInit(){
  servo.attach(servoPin);
}

void MyServoSend(uint16_t data){
  servo.attach(servoPin);
  servo.writeMicroseconds(data);
}
