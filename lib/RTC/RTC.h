#pragma once
#include "RTClib.h"

class RTC
{
public:
    RTC();

    bool connect();
    DateTime now();
    void setDate();

    void writeNVRAMData(uint8_t *buf, uint8_t size, uint8_t address);
    void readNVRAMData(uint8_t *buf, uint8_t size, uint8_t address);

private:
    bool _isConnected = false;
    RTC_DS1307* _rtc;
};