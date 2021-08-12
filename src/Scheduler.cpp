#include "Scheduler.h"
#include "config.h"

Scheduler::Scheduler(UserInput* userInput, RTC* rtc, Storage* storage){
    _userInput = userInput;
    _rtc = rtc;
    _storage = storage;
}

bool Scheduler::checkGroup(int groupId){ 
    //Serial.print(F("Checking group "));Serial.println(groupId);
    auto historicalData = _storage->getHistoricalData();
    //printHistoricalData(&historicalData);
    if(historicalData._magicNumber != HISTORICAL_DATA_MAGIC_NUMBER){
        _storage->restoreMagicNumber();
    }

    auto now = _rtc->now();
    //Serial.print(F("Time Now: "));printDateTime(&now);
    auto last = DateTime(historicalData.unixTime);
    //Serial.print(F("Time Last: "));printDateTime(&last);

    if(isScheduledWateringMode()){
        //Serial.println(F("Checking schedule..."));
        if(now.hour() == WATERING_TIME_HOUR && now.minute() >= WATERING_TIME_MINUTE){
            if(groupId == 0 && (historicalData._magicNumber != HISTORICAL_DATA_MAGIC_NUMBER || !historicalData.isGroup1Done))return true;
            if(groupId == 1 && (historicalData._magicNumber != HISTORICAL_DATA_MAGIC_NUMBER || !historicalData.isGroup2Done))return true;
            if(groupId == 2 && (historicalData._magicNumber != HISTORICAL_DATA_MAGIC_NUMBER || !historicalData.isGroup3Done))return true;
        }
    }
    else {
        // CHECK Moisture sensors
        //Serial.println("Checking sensors...");
    }

    if(historicalData._magicNumber == HISTORICAL_DATA_MAGIC_NUMBER){
        if(((now - last).totalseconds() / 60 / 60) >= WATERING_TIME_DAYS_INTERVAL*24 && 
        (historicalData.isGroup1Done || historicalData.isGroup2Done || historicalData.isGroup3Done)){
            clearDoneMarks(); 
        }  
    }

    return false; 
}

void Scheduler::markAsDone(int groupId){
    //Serial.print("Marking as done group ");Serial.println(groupId);
    HistoricalData data = _storage->getHistoricalData();
    //Serial.print("Old ");printHistoricalData(&data);
    data.unixTime = _rtc->now().unixtime();
    if(groupId == 0)data.isGroup1Done = true;
    else if(groupId == 1)data.isGroup2Done = true;
    else if(groupId == 2)data.isGroup3Done = true;

    _storage->writeHistoricalData(data);
    //Serial.print("New ");printHistoricalData(&_storage->getHistoricalData());
}

void Scheduler::clearDoneMarks(){
    //Serial.print("Clear done marks");
    HistoricalData data = _storage->getHistoricalData();
    data.isGroup1Done = false;
    data.isGroup2Done = false;
    data.isGroup3Done = false;
    _storage->writeHistoricalData(data);
}

//Setup purposes
void Scheduler::setupLastDate(){
    HistoricalData data = _storage->getHistoricalData();
    data.isGroup1Done = true;
    data.isGroup2Done = true;
    data.isGroup3Done = false;
    data.unixTime = DateTime(2021, 8, 12,    9, 0, 0).unixtime();
    _storage->writeHistoricalData(data);
}

bool Scheduler::isScheduledWateringMode(){
    return _userInput->isScheduledWateringMode();
}

void Scheduler::printHistoricalData(HistoricalData* historicalData){
    Serial.print(F("Historical data: ["));Serial.print(historicalData->unixTime);Serial.print(",");
    Serial.print(historicalData->isGroup1Done);Serial.print(",");Serial.print(historicalData->isGroup2Done);Serial.print(",");Serial.print(historicalData->isGroup3Done);
    Serial.print(",");Serial.print(historicalData->_magicNumber);Serial.println("]");
}

void Scheduler::printDateTime(DateTime* date){
    Serial.print(date->year(), DEC);Serial.print('/');Serial.print(date->month(), DEC);Serial.print('/');Serial.print(date->day(), DEC);
    Serial.print(' ');
    Serial.print(date->hour(), DEC);Serial.print(':');Serial.print(date->minute(), DEC);Serial.print(':');Serial.print(date->second(), DEC);Serial.println();
}