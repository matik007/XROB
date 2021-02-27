// Управвление Машинкой по стенке

#define SERIAL 1 // 1 - вкл вывод по uart, 0 - выкл

#define WALL_LEFT 1
#define WALL_RIGHT 2

#define WALL_DISTNACE 450
#define KI 0.2

#include "MyServo.h"
#include "Motor.h"
#include "Receiver.h"
#include "Lidar.h"
#include "MyI2C.h"
#include "PID.h"

void setup() {
#if SERIAL
  Serial.begin(9600);
#endif 
  Serial2.begin(9600); // bt модуль 
  ReceiverInit();
  MotorInit();
  MyServoInit();
  LidarInit();
  MyI2CInit();

  Serial.println("setup OK!");
}
uint8_t ang = 90;

void BtListen(){
  if(Serial2.available()){
    
    //Serial2.println("OK");
    
    switch(Serial2.read()){
      case '+':
        ang+=10;
        ang = constrain(ang, 0, 180);
        servo.write(ang);
        Serial2.println(ang);
        break;
      case '-':
        ang-=10;
        ang = constrain(ang, 0, 180);
        servo.write(ang);
        Serial2.println(ang);
        break;
      case '0':
        STATE = STOP;
        Serial2.println("stop");
        break;
      case '1':
        STATE = AUTO_CONTROL;
        Serial2.println("auto control");
        break;
      case '2':
        STATE = MANUAL_CONTROL;
        Serial2.println("manual control");
        break;
      case 'w':
        MotorForward();  
        break;
      case 's':
        MotorBack();  
        break;
    }
     //float data = Serial2.parseFloat(); // для задания коэфизиента
    // Serial2.println(data/100);
  }
}

int I = 0, set = 300, in , dt, kI;

int ComputeSignal(float set, float minAngle, float maxAngle, float kI){

   float in = LidarGetDistanceFromeScaneAngle(minAngle, maxAngle);
  
  I = I + (set - in);
  
  I = I*kI;
  Serial.print(" Dis = ");
  Serial.println(in);
  Serial.print("ang = ");

  if(maxAngle > 90){ // целим влево
    I = 90 + I;
  } else if(maxAngle < 90){ // целим вправо
    I = 90 - I;
  }

  
  Serial.println(I);
  return constrain(I, 40, 140);
}

void MapControl(){

  Serial2.println("WELLCOME_TO_MAP");
  
  do{
     BtListen();
    servo.write(ComputeSignal(WALL_DISTNACE, 359, 1, KI));
  } while(distance > WALL_DISTNACE+100);
  Serial2.println("WALL_LEFT");
  
  
  while(LidarGetDistanceFromeScaneAngle(359, 1) > WALL_DISTNACE * 3){
     BtListen();
    servo.write(ComputeSignal(WALL_DISTNACE, 179, 181, KI));
  }
  
  Serial2.println("WALL_RIGHT");
  
  do{
    BtListen(); 
    servo.write(ComputeSignal(WALL_DISTNACE, 359, 1, KI));
  } while(distance > WALL_DISTNACE);
  
  STATE = STOP;
  Serial2.println("stop");  
}

void loop() {
  BtListen();
  
  if(STATE == STOP){
    MotorStop();
    LidarStop();
  } else if(STATE == MANUAL_CONTROL){
    ReceiverControl();
    LidarStop();
  }else if(STATE == AUTO_CONTROL){
    servo.write(ComputeSignal(WALL_DISTNACE, 179, 181, KI));
    MotorForward();
    //if(distance > WALL_DISTNACE*2){
    //  MapControl();
   // }
  }
}
