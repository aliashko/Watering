#include "MotorsController.h"
#include "Arduino.h"
#include "config.h"

MotorsController::MotorsController(){
    for (int motorPin : MOTOR_PIN){
        pinMode(motorPin, OUTPUT);digitalWrite(motorPin, 0);
    }
}

void MotorsController::turn(int motorId, bool active){
    digitalWrite(MOTOR_PIN[motorId], active);
}