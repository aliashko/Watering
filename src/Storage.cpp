#include "Storage.h"
#include "Arduino.h"

Storage::Storage(RTC* rtc){
    _rtc = rtc;
}

HistoricalData Storage::getHistoricalData(){
    HistoricalData data;
    byte buffer[sizeof(data)];
    _rtc->readNVRAMData(buffer, sizeof(data), 0);
    readData((byte*)&data, sizeof(data), buffer);
    
    return data;
}

void Storage::writeHistoricalData(HistoricalData data){
    byte buffer[sizeof(data)];
    writeData((byte*)&data, sizeof(data), buffer);
    _rtc->writeNVRAMData(buffer, sizeof(data), 0);
}

void Storage::restoreMagicNumber(){
    auto data = getHistoricalData();
    data._magicNumber = HISTORICAL_DATA_MAGIC_NUMBER;
    writeHistoricalData(data);
}

void Storage::writeData(byte* data, int length, byte* dest) {
  int i = 0;
  while (length--) {
    dest[i] = *(data + i);
    i++;
  }
}
void Storage::readData(byte* data, int length, byte* source) {
  int i = 0;
  while (length--) {
    *(data + i) = source[i];
    i++;
  }
}