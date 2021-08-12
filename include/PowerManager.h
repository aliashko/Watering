#pragma once
#include "Arduino.h"

class PowerManager
{
public:
    PowerManager();

    bool isRtcBatteryOk();
    float getBatteryVoltage();    
    void sleep(int seconds);

private:
    float getVoltageFromAnalogPin(uint8_t pin);
};