#pragma once
#include "Bonus.h"
#include <SFML/Graphics.hpp>
#include <vector>

class BonusDecreasePlatform :
    public Bonus
{
public:
    Platform& platform;
    
    BonusDecreasePlatform(sf::Vector2f position, Platform& platform);
    virtual void destroy() override;
};

class BonusIncreasePlatform :

    public Bonus
{
public:
    Platform& platform;
    BonusIncreasePlatform(sf::Vector2f position, Platform& platform);
    virtual void destroy() override;
};

class BonusIncreaseBallSpeed :
    public Bonus
{
public:
    Ball& ball;
    BonusIncreaseBallSpeed(sf::Vector2f position, Ball& ball);
    virtual void destroy() override;
};

class BonusDecreaseBallSpeed :
    public Bonus
{
public:
    Ball& ball;
    BonusDecreaseBallSpeed(sf::Vector2f position, Ball& ball);
    virtual void destroy() override;
};


class BonusStickToPlatform :
    public Bonus
{
public:
    Ball& ball;
    BonusStickToPlatform(sf::Vector2f position, Ball& ball);
    virtual void destroy() override;
};

class BonusBall :
    public Bonus
{
public:
    Platform &platform;
    BonusBall(sf::Vector2f position, Platform& );
    virtual void destroy() override;
};

class BonusFloor :
    public Bonus
{
public:
    Platform& platform;
    BonusFloor(sf::Vector2f position, Platform& platform);
    virtual void destroy() override;
};