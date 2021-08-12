#pragma once

class MotorsController
{
public:
    MotorsController();

    void turn(int motorId, bool active);
};