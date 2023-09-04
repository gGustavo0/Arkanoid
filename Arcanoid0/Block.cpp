
#include "Block.h"
#include <iostream>
#include <cstdlib>


Block::Block(int x, int y, std::list<Bonus*>& bonuses, int size): block(*new sf::RectangleShape(sf::Vector2f(size, size))), bonuses(bonuses) {
	block.setOutlineThickness(-5);
	block.setOutlineColor(sf::Color::Black);
	block.setPosition(sf::Vector2f(x, y));
	block.setFillColor(sf::Color::Green);
	int r =  rand() % 37;
	if (!texture.create(200, 200))
	{
		// error...
	}

	switch (r)
	{
	default:
		bonusType = BonusType::NONE;
		break;
	case 0:
		bonusType = BonusType::UNDESTRUCTUBLE;
		block.setFillColor(sf::Color::Cyan);
		hp = -1;
		break;
	case 1:
		bonusType = BonusType::BALL_STICKED;
		if (!texture.loadFromFile("stick.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		break;
	case 2:
		bonusType = BonusType::DECREASE_BALL_SPEED;
		if (!texture.loadFromFile("arrowDown.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		break;
	case 3:
		bonusType = BonusType::INCREASE_BALL_SPEED;
		if (!texture.loadFromFile("arrowUp.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		break;
	case 4:
		bonusType = BonusType::INCREASE_PLATFORM;
		if (!texture.loadFromFile("increase.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		break;
	case 5:
		bonusType = BonusType::DECREASE_PLATFORM;
		if (!texture.loadFromFile("decrease.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		break;
	case 6:
		bonusType = BonusType::FLOOR;
		if (!texture.loadFromFile("floor.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		break;
	case 7:
		bonusType = BonusType::SECOND_BALL;
		if (!texture.loadFromFile("ball.png"))
		{
			// error...
		}
		block.setTexture(&texture);
		block.setTextureRect(sf::IntRect(100, 100, 50, 50));
		break;
	}
	
	
}

void Block::getHit(Counter& counter, Ball& ball, Platform& platform) {
	if (hp == 3)
	{
		block.setFillColor(sf::Color::Yellow);
	}
	if (hp == 2)
	{
		block.setFillColor(sf::Color::Red);
	}
	if (hp == 1)
	{
		counter.plusPoint();
		switch (bonusType)
		{
		case BonusType::NONE:
			break;
		case BonusType::UNDESTRUCTUBLE:
			hp = -1;
			break;
		case BonusType::INCREASE_BALL_SPEED:
			bonuses.push_back(new BonusIncreaseBallSpeed(block.getPosition(),ball));
			break;
		case BonusType::DECREASE_BALL_SPEED:
			bonuses.push_back(new BonusDecreaseBallSpeed(block.getPosition(), ball));
			break;
		case BonusType::INCREASE_PLATFORM:
			bonuses.push_back(new BonusIncreasePlatform(block.getPosition(), platform));
			break;
		case BonusType::DECREASE_PLATFORM:
			bonuses.push_back(new BonusDecreasePlatform(block.getPosition(), platform));
			break;
		case BonusType::BALL_STICKED:
			bonuses.push_back(new BonusStickToPlatform(block.getPosition(), ball));
			break;
		case BonusType::FLOOR:
			bonuses.push_back(new BonusFloor(block.getPosition(), platform));
			break;
		case BonusType::SECOND_BALL:
			bonuses.push_back(new BonusBall(block.getPosition(), platform));
			break;
		default:
			break;
		}
	}
	if (hp > 0) { hp--; }
	cout << "BLOCK" << endl;
	cout << bonuses.size() << endl;
}

bool Block::exists() {
	return hp != 0;
}