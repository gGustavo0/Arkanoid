#pragma once

#include    "Bonus.h"
#include    <SFML/Graphics.hpp>
#include    <vector>

class BonusDecreasePlatform : public Bonus {
private:
    Platform& platform;
public:
    BonusDecreasePlatform(sf::Vector2f position, Platform& platform);
    virtual void destroy() override;
};

class BonusIncreasePlatform : public Bonus {
private:
    Platform& platform;
public:
    BonusIncreasePlatform(sf::Vector2f position, Platform& platform);
    virtual void destroy() override;
};

class BonusIncreaseBallSpeed : public Bonus {
private:
    Ball& ball;
public:
    BonusIncreaseBallSpeed(sf::Vector2f position, Ball& ball);
    virtual void destroy() override;
};

class BonusDecreaseBallSpeed : public Bonus {
private:
    Ball& ball;
public:
    BonusDecreaseBallSpeed(sf::Vector2f position, Ball& ball);
    virtual void destroy() override;
};


class BonusStickToPlatform : public Bonus {
private:
    Ball& ball;
public:
    BonusStickToPlatform(sf::Vector2f position, Ball& ball);
    virtual void destroy() override;
};

class BonusBall : public Bonus {
private:
    Platform& platform;
public:
    BonusBall(sf::Vector2f position, Platform& );
    virtual void destroy() override;
};

class BonusFloor : public Bonus {
private:
    Platform& platform;
public:
    BonusFloor(sf::Vector2f position, Platform& platform);
    virtual void destroy() override;
};