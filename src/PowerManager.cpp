#include "PowerManager.h"
#include "config.h"
#include <GyverPower.h>

PowerManager::PowerManager(){
    pinMode(BATTERY_VOLTAGE_PIN, INPUT);
}

bool PowerManager::isRtcBatteryOk(){
    auto voltage = getVoltageFromAnalogPin(BATTERY_VOLTAGE_PIN);    
    //Serial.print("Battery Voltage ");Serial.println(voltage);
    return voltage >= 2;
}

float PowerManager::getBatteryVoltage(){
    auto voltage = getVoltageFromAnalogPin(BATTERY_VOLTAGE_PIN);    
    return voltage;
}

void PowerManager::sleep(int seconds){
    delay(seconds * 1000);
    //power.sleepDelay(seconds * 1000);
}


float PowerManager::getVoltageFromAnalogPin(uint8_t pin){
    return (float)(analogRead(pin) * 5.0) / 1024;
}