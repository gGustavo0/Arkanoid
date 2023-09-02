#pragma once
#include "Bonus.h"

class BonusDecreasePlatform :
    public Bonus
{
    Platform& platform;
    ~BonusDecreasePlatform();
};

class BonusIncreasePlatform :

    public Bonus
{
    Platform& platform;
    ~BonusIncreasePlatform();
};

class BonusIncreaseBallSpeed :
    public Bonus
{
    Ball& ball;
    ~BonusIncreaseBallSpeed();
};

class BonusDecreaseBallSpeed :
    public Bonus
{
    Ball& ball;
    ~BonusDecreaseBallSpeed();
};


class BonusStickToPlatform :
    public Bonus
{
    Ball& ball;
    Platform& platform;
    ~BonusStickToPlatform();
};