#pragma once

#include "Ball.h"
#include "Block.h"
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

	void ballScreenCollision(Ball& ball, sf::RenderWindow& window);
	void platformBallCollision(Ball& ball, Platform& platform);
	void ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float);
	void checkCollisions(Ball& ball, vector<vector<Block>> &blocks, Platform &platform, sf::RenderWindow& window, float);
	bool intersects(sf::Shape&, sf::Shape&);
};

