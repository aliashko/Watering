#pragma once
#include <Arduino.h>

const int SLEEP_DURATION = 5;

// SETTINGS FOR SCHEDULED WATERING
const bool WATERING_ACTIVE[] = {true, true, false};

const int WATERING_TIME_HOUR = 9;
const int WATERING_TIME_MINUTE = 0;
const int WATERING_TIME_DAYS_INTERVAL = 6;
const int WATERING_DURATION_SEC[] = {6, 10, 10};//10,12

// MOTORS MOSFETS
const uint8_t MOTOR_PIN[] = {3,2,4};

// RTC
const uint8_t RTC_I2C_ADDRESS = 0x68;
const uint8_t OLED_I2C_ADDRESS = 0x3c;

// VOLTAGE SENSORS SETTINGS
const uint8_t BATTERY_VOLTAGE_PIN = A0;

// MOISTURE SENSORS
const uint8_t MOISTURE_SENSOR[] = {A1, A2, A3};

// BUTTONS
const uint8_t BUTTON_PIN[] = {6, 5, 7};
const uint8_t SWITCH_WATERING_MODE = 10;

// LEDS
const uint8_t LED_LOW_BATTERY = 8;
const uint8_t LED_WARNING = 13;