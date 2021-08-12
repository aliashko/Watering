// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTC.h"

RTC::RTC(){
    _rtc = new RTC_DS1307();
}

bool RTC::connect() {
    if (!_rtc->begin()) {
        return false;
    }

    if (!_rtc->isrunning()) {
        setDate();
    }

    return true;
}

DateTime RTC::now() {
    return _rtc->now();
}

void RTC::setDate() {
    _rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RTC::writeNVRAMData(uint8_t *buf, uint8_t size, uint8_t address){
    _rtc->writenvram(address, buf, size);
}

void RTC::readNVRAMData(uint8_t *buf, uint8_t size, uint8_t address){
     _rtc->readnvram(buf, size, address);
}