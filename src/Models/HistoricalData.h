#pragma once
#include "Arduino.h"

const uint32_t HISTORICAL_DATA_MAGIC_NUMBER = 12345678;

struct HistoricalData {    
  uint32_t unixTime;
  bool isGroup1Done;
  bool isGroup2Done;
  bool isGroup3Done;

  uint32_t _magicNumber = HISTORICAL_DATA_MAGIC_NUMBER;
};