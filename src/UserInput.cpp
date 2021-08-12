#include "UserInput.h"
#include "Arduino.h"
#include "config.h"

UserInput::UserInput(){
    for (int buttonPin : BUTTON_PIN){
        pinMode(buttonPin, INPUT_PULLUP);
    }

    pinMode(SWITCH_WATERING_MODE, INPUT_PULLUP);
}

bool UserInput::checkAnyButtonPressed(){
    for (int i = 0; i < sizeof(MOTOR_PIN); i++){
        if(checkMotorButton(i))return true;
    }
    return false;
}

bool UserInput::checkMotorButton(int motorId){
    for(int i=0;i<5;i++){
        if(digitalRead(BUTTON_PIN[motorId]) == LOW) {            
            return true;
        }
    }
    return false;
}

bool UserInput::isScheduledWateringMode(){
    for(int i=0;i<5;i++){
        if(!digitalRead(SWITCH_WATERING_MODE)) return false;
    }
    return true;
}