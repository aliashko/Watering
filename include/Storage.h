#pragma once
#include "RTC.h"
#include "Models/HistoricalData.h"

class Storage
{
public:
    Storage(RTC* rtc);

    HistoricalData getHistoricalData();
    void writeHistoricalData(HistoricalData data);
    void restoreMagicNumber();

private:
    RTC* _rtc; 
    void writeData(byte* data, int length, byte* dest);
    void readData(byte* data, int length, byte* source);
};