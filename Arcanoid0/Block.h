#pragma once
#include "Block.h"
#include "Bonus.h"
#include "Bonuses.h"
#include "Counter.h"
#include <vector>;
#include <SFML/Graphics.hpp>
#include <list>
using namespace std;

enum class BonusType {
	NONE,
	UNDESTRUCTUBLE,
	INCREASE_BALL_SPEED,
	DECREASE_BALL_SPEED,
	INCREASE_PLATFORM,
	DECREASE_PLATFORM,
	BALL_STICKED,
	FLOOR,
	SECOND_BALL
};

#define SIZE 50

class Block
{
public:
	int hp = 1;
	sf::RectangleShape    block;
	list<Bonus*>& bonuses;
	BonusType bonusType;
	sf::Texture texture;
	Block(int x, int y, list<Bonus*>&, int size = SIZE);
	
	void getHit(Counter& counter, Ball&, Platform&);
	bool exists();


};

