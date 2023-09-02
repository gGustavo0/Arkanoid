#include "Bonuses.h"

BonusDecreasePlatform::~BonusDecreasePlatform() {
	platform.platform.setSize(sf::Vector2f(platform.platform.getSize().x - 10, platform.platform.getSize().y));
}

BonusIncreasePlatform::~BonusIncreasePlatform() {
	platform.platform.setSize(sf::Vector2f(platform.platform.getSize().x + 10, platform.platform.getSize().y));
}

BonusIncreaseBallSpeed::~BonusIncreaseBallSpeed() {
	ball.speedX += 10;
	ball.speedY += 10;
}

BonusDecreaseBallSpeed::~BonusDecreaseBallSpeed() {
	ball.speedX -= 10;
	ball.speedY -= 10;
}

BonusStickToPlatform::~BonusStickToPlatform() {
	ball.toStick = true;
}