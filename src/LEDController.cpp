#include "LEDController.h"
#include "Arduino.h"
#include "config.h"

LEDController::LEDController(){
    pinMode(LED_WARNING, OUTPUT);digitalWrite(LED_WARNING, 0);
    pinMode(LED_LOW_BATTERY, OUTPUT);digitalWrite(LED_LOW_BATTERY, 1);
}

void LEDController::warningLed( bool active){
    digitalWrite(LED_WARNING, active);
}
void LEDController::batteryLow(bool active){
    digitalWrite(LED_LOW_BATTERY, !active);
}

void LEDController::blinkError(){
    digitalWrite(LED_WARNING, 1);delay(500);
    digitalWrite(LED_WARNING, 0);delay(500);
    digitalWrite(LED_WARNING, 1);delay(500);
    digitalWrite(LED_WARNING, 0);delay(500);
    digitalWrite(LED_WARNING, 1);delay(500);
    digitalWrite(LED_WARNING, 0);delay(500);
}

void LEDController::blinkStartup(){
    batteryLow(1);delay(300);
    batteryLow(0);delay(300);
    batteryLow(1);delay(300);
    batteryLow(0);delay(300);
    batteryLow(1);delay(300);
    batteryLow(0);delay(300);
}