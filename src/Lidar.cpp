#include "Lidar.h"

// You need to create an driver instance 
RPLidar lidar;

#define RPLIDAR_MOTOR 5 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal 

float distance;
float angle;
bool startBit;
byte quality;
                    

void LidarInit(){
   // bind the RPLIDAR driver to the arduino hardware serial
  lidar.begin(Serial3); // Arduino Mega

  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void LidarGetData(){
  if (IS_OK(lidar.waitPoint())) {
    distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
       
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}

void LidarStop(){
  analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
}

float LidarGetDistanceFromeScaneAngle(float minAngle, float maxAngle){
  while(true){
    LidarGetData();
    if(minAngle > maxAngle){
      if((angle > minAngle || angle < maxAngle) && distance) break;
    } else {
      if(angle > minAngle && angle < maxAngle && distance) break;  
    }  
  }
  return distance;
}
