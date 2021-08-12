#pragma once

class UserInput
{
public:
    UserInput();

    bool checkMotorButton(int motorId);
    bool checkAnyButtonPressed();    
    bool isScheduledWateringMode();

    bool isInteractiveMode = true;
    long interactiveModeStartedTime;
};