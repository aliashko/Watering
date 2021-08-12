#include "DisplayController.h"
#include "config.h"

DisplayController::DisplayController(){
    _display = new SSOLED();
}

bool DisplayController::connect(){
    auto result = oledInit(_display, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 400000L);
    if (result == OLED_NOT_FOUND) return false;
    return true;
}
void DisplayController::showStartupScreen(){
    clearScreen();
    oledWriteString(_display, 0,16,0,(char *)"Starting...", FONT_NORMAL, 0, 1);
}
void DisplayController::showStatus(DateTime timeNow, HistoricalData historicalData, float batteryVoltage){
    clearScreen();
    oledWriteString(_display, 0,0,0,(char *)"Now: ", FONT_NORMAL, 0, 1);    
    oledWriteString(_display, 0,0,2,(char *)timeToString(timeNow).c_str(), FONT_NORMAL, 0, 1);

    oledWriteString(_display, 0,0,3,(char *)"Battery V: ", FONT_NORMAL, 0, 1);    
    oledWriteString(_display, 0,85,3,(char *)String(batteryVoltage).c_str(), FONT_NORMAL, 0, 1);

    oledWriteString(_display, 0,0,5,(char *)"Last: ", FONT_NORMAL, 0, 1);    
    oledWriteString(_display, 0,0,6,(char *)timeToString(DateTime(historicalData.unixTime)).c_str(), FONT_NORMAL, 0, 1);

    oledWriteString(_display, 0,0,7,(char *)"Done: ", FONT_NORMAL, 0, 1);    
    oledWriteString(_display, 0,45,7,(char *)(String(historicalData.isGroup1Done)+"/"+String(historicalData.isGroup2Done)+"/"+String(historicalData.isGroup3Done)).c_str(), FONT_NORMAL, 0, 1);
}
void DisplayController::clearScreen(){
    oledFill(_display, 0x0, 1);
}

String DisplayController::timeToString(DateTime time){
    String str = String(time.day()) + "." + time.month() + "." + time.year() + " " + time.hour() + ":" + time.minute();
    return str;
}