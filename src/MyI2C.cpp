#include "MyI2C.h"

char x;

uint8_t STATE = STOP;

void MyI2CInit(){
  Wire.begin(0x03);
  Wire.onReceive(receiveEvent);
}

void receiveEvent() {
  x = Wire.read(); // Получаем значения х от основной платы
  Serial.println(x);
  switch(x){
    case '0': 
      STATE = STOP;
      break;
      case '1': 
      STATE = AUTO_CONTROL;
      break;
      case '2': 
      STATE = MANUAL_CONTROL;
      break;
  }
}
