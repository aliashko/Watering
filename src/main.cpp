#include <Arduino.h>
#include <RTC.h>
#include <UserInput.h>
#include <LEDController.h>
#include <MotorsController.h>
#include <Scheduler.h>
#include <PowerManager.h>
#include <DisplayController.h>
#include <config.h>

RTC *rtc;
UserInput *userInput;
LEDController *ledController;
MotorsController *motorsController;
Scheduler *scheduler;
Storage *storage;
PowerManager *powerManager;
DisplayController *displayController;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting... ");

  rtc = new RTC();
  userInput = new UserInput();
  ledController = new LEDController();
  motorsController = new MotorsController();
  storage = new Storage(rtc);
  powerManager = new PowerManager();
  displayController = new DisplayController();
  scheduler = new Scheduler(userInput, rtc, storage);

  if(!displayController->connect())Serial.println("Display not found!");
  displayController->showStartupScreen();

  while(!rtc->connect() && userInput->isScheduledWateringMode()){
    Serial.println("No RTC connected!");
    ledController->blinkError();
    delay(1000);
  }

  Serial.println("done");
  ledController->blinkStartup();
  displayController->clearScreen();
  
  //scheduler->setupLastDate();///COMMENT AFTER SETUP!!!
}

void checkBattery(){
  auto batteryOk = powerManager->isRtcBatteryOk();
  ledController->batteryLow(!batteryOk);
}

void loop() {
  checkBattery();  
  if(userInput->checkAnyButtonPressed()){
    userInput->isInteractiveMode = true;
    userInput->interactiveModeStartedTime = millis();
  }

  if(millis() - userInput->interactiveModeStartedTime > 20000){
    userInput->isInteractiveMode = false;
  }

  if(userInput->isInteractiveMode){
    displayController->showStatus(rtc->now(), storage->getHistoricalData(), powerManager->getBatteryVoltage());
  }
  else displayController->clearScreen();

  for (int i = 0; i < (int)sizeof(WATERING_ACTIVE); i++){
      if(!WATERING_ACTIVE[i])continue;
      if(scheduler->checkGroup(i)){
          Serial.print(F("Start watering Group #"));Serial.println(i);
          scheduler->markAsDone(i);
          motorsController->turn(i, true);
          delay(WATERING_DURATION_SEC[i] * 1000);
          motorsController->turn(i, false);
          Serial.print(F("Stop watering Group #"));Serial.println(i);
      }
  }

  //Serial.println("sleep...");
  powerManager->sleep(SLEEP_DURATION);
}