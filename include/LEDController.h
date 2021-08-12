#pragma once

class LEDController
{
public:
    LEDController();

    void warningLed(bool active);
    void batteryLow(bool active);

    void blinkError();
    void blinkStartup();   
};