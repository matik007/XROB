#include "Motor.h"

uint8_t MA = A6, MB = A5, EN = 6, PWM = 7; // контакты мотора

void MotorInit(){
  pinMode(MA, OUTPUT);
  pinMode(MB, OUTPUT);
}

void MotorStop() {
  digitalWrite(MA, LOW);
  digitalWrite(MB, LOW);
  digitalWrite(EN, LOW);
  analogWrite(PWM, 0);
}

void MotorForward(uint8_t sp) {
#if SERIAL
  Serial.println(sp);
#endif
  digitalWrite(MA, HIGH);
  digitalWrite(MB, LOW);
  digitalWrite(EN, HIGH);
  analogWrite(PWM, sp);
}

void MotorForwardLidar(uint8_t minAngle, uint8_t maxAngle){
  for(int i = 0; i < 100; i++){
    if(LidarGetDistanceFromeScaneAngle(minAngle, maxAngle) < 300){
      MotorStop();
      break;
    }
  }
  MotorForward();
}

void MotorBack(uint8_t sp) {
  digitalWrite(MA, LOW);
  digitalWrite(MB, HIGH);
  digitalWrite(EN, HIGH);
  analogWrite(PWM, sp);
}
