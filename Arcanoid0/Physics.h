#pragma once

#include "Ball.h"
#include "Counter.h"
#include "Block.h"
#include "Bonus.h"
#include "Bonuses.h"
#include <vector>
#include <list>
#include                           <SFML/Graphics.hpp>
#include                           "Platform.h";
using namespace std;

enum class Side {
	HORIZONTAL,
	VERTICAL,
	CORNER
};

class Physics
{
public:
	Side side(Ball&ball, Block& block);
	bool screenBonusCollision(sf::RectangleShape bonus, sf::RenderWindow&);
	void ballScreenCollision(Ball& ball, sf::RenderWindow& window, Counter&, Platform&);
	bool bonusPlatformCollision(sf::RectangleShape bonus, Platform& platform);
	void platformBallCollision(Ball& ball, Platform& platform, Counter&, sf::RenderWindow&);
	void ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float, Counter&, Platform&);
	void checkCollisions(Ball& ball, vector<vector<Block>> &blocks, Platform &platform, sf::RenderWindow& window, float, Counter&);
	bool intersects(sf::Shape&, sf::Shape&);
};

