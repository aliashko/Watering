#pragma once
#include "UserInput.h"
#include "RTC.h"
#include "Storage.h"

class Scheduler
{
public:
    Scheduler(UserInput* userInput, RTC* rtc, Storage* storage);

    bool checkGroup(int groupId);
    void markAsDone(int groupId);
    void setupLastDate();

private:
    UserInput* _userInput;   
    RTC* _rtc; 
    Storage* _storage;

    bool isScheduledWateringMode();
    void clearDoneMarks();
    static void printHistoricalData(HistoricalData* historicalData);
    static void printDateTime(DateTime* date);
};