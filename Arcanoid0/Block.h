#pragma once
#include "Block.h"
#include "Bonus.h"
#include "Counter.h"
#include <vector>;
#include <SFML/Graphics.hpp>
using namespace std;

enum class BonusType {
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
	int hp = 3;
	sf::RectangleShape    block;
	vector<Bonus>& bonuses;
	BonusType bonusType;
	sf::Texture texture;
	Block(int x, int y, vector<Bonus>&, int size = SIZE);
	
	void getHit(Counter& counter);
	bool exists();


};

