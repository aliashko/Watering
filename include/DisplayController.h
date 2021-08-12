#pragma once
#include <Arduino.h>
#include <ss_oled.h>
#include <RTC.h>
#include <Models/HistoricalData.h>

// Use -1 for the Wire library default pins
// or specify the pin numbers to use with the Wire library or bit banging on any GPIO pins
// These are the pin numbers for the M5Stack Atom default I2C
#define SDA_PIN -1
#define SCL_PIN -1
// Set this to -1 to disable or the GPIO pin number connected to the reset
// line of your display if it requires an external reset
#define RESET_PIN -1
// let ss_oled figure out the display address
#define OLED_ADDR -1
// don't rotate the display
#define FLIP180 1
// don't invert the display
#define INVERT 0
// Bit-Bang the I2C bus
#define USE_HW_I2C 1

// Change these if you're using a different OLED display
#define MY_OLED OLED_128x64
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
//#define MY_OLED OLED_64x32
//#define OLED_WIDTH 64
//#define OLED_HEIGHT 32

class DisplayController
{
public:
    DisplayController();

    bool connect();  
    void showStartupScreen();  
    void showStatus(DateTime timeNow, HistoricalData historicalData, float batteryVoltage);      
    void clearScreen();

private:
    SSOLED *_display;
    String timeToString(DateTime time);
};