#pragma once

#include "Ball.h"
#include "Counter.h"
#include "Block.h"
#include "Bonus.h"
#include <vector>
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
	bool isFloor = false;
	Side side(Ball&ball, Block& block);

	void ballScreenCollision(Ball& ball, sf::RenderWindow& window);
	void bonusPlatformCollision(Bonus& bonus, Platform& platform);
	void platformBallCollision(Ball& ball, Platform& platform, Counter&, sf::RenderWindow&);
	void ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float, Counter&);
	void checkCollisions(Ball& ball, vector<vector<Block>> &blocks, Platform &platform, sf::RenderWindow& window, float, Counter&);
	bool intersects(sf::Shape&, sf::Shape&);
};

