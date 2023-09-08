#include "Bonuses.h"

void BonusDecreasePlatform::destroy() {
	platform.setSize(platform.getSize().x - 10, platform.getSize().y);
}

BonusDecreasePlatform::BonusDecreasePlatform(sf::Vector2f position, Platform& platform): Bonus(position), platform(platform){}

void BonusIncreasePlatform::destroy() {
	platform.setSize(platform.getSize().x + 10, platform.getSize().y);
}
BonusIncreasePlatform::BonusIncreasePlatform(sf::Vector2f position, Platform& platform) : Bonus(position), platform(platform) {}

void BonusIncreaseBallSpeed::destroy() {
	ball.changeSpeed(20, 20);
}
BonusIncreaseBallSpeed::BonusIncreaseBallSpeed(sf::Vector2f position, Ball& ball) : Bonus(position), ball(ball) {}

void BonusDecreaseBallSpeed::destroy() {
	ball.changeSpeed(-20, -20);
}

BonusDecreaseBallSpeed::BonusDecreaseBallSpeed(sf::Vector2f position, Ball& ball) : Bonus(position), ball(ball) {}

void BonusStickToPlatform::destroy() {
	ball.toStick = true;
}

BonusStickToPlatform::BonusStickToPlatform(sf::Vector2f position, Ball& ball) : Bonus(position), ball(ball) {}

void BonusBall::destroy() {
	platform.spawnNewBall = true;
}

BonusBall::BonusBall(sf::Vector2f position, Platform& platform) : Bonus(position), platform(platform) {}

void BonusFloor::destroy() {
	platform.isFloor = true;
}

BonusFloor::BonusFloor(sf::Vector2f position, Platform &platform) : Bonus(position), platform(platform) {}