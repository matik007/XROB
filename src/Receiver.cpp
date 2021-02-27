// в положении 70 на 30 ручки газа сняты значения:
// центр (стоп) - 1311 ~ 1327
// от себя макс (полный назад) - 990 ~ 991
// на себя макс (полный вперёд) - 1437 ~ 1444

// в положении 50 на 50 ручки газа сняты значения:
// центр (стоп) - 1489 ~ 1505
// от себя макс (полный назад) - 990 ~ 991
// на себя макс (полный вперёд) - 1607 ~ 1614



#include "Receiver.h"

uint8_t ch1 = 4, ch2 = 3;

uint16_t dataCh1, dataCh2; // данный канала 1 и 2
int16_t motorSpeed = 0;

void ReceiverInit(){
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
}

void ReadReceiver() {
  
  dataCh1 = pulseIn(ch1, HIGH);
  dataCh2 = pulseIn(ch2, HIGH);

  Serial.print(dataCh1);
  Serial.print(" || ");
  Serial.println(dataCh2);

}

void ReceiverControl(){
  ReadReceiver();
  if (dataCh2 < 1300) {
    motorSpeed = map(dataCh2, 990, 1300, 255, 0);
    motorSpeed = constrain(motorSpeed, 0, 255);
    MotorBack(motorSpeed);
  } else if (dataCh2 > 1350) {
    motorSpeed = map(dataCh2, 1350, 1435, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255);
    MotorForward(motorSpeed);
  } else {
    motorSpeed = 0;
    MotorStop();
  }
  MyServoSend(dataCh1);

#if SERIAL
  Serial.print("\nSpeed = ");
  Serial.println(motorSpeed);
#endif
}
