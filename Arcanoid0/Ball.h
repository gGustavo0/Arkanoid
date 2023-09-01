#pragma once

#include "Block.h"
#include <vector>
#include                           <SFML/Graphics.hpp>

class Ball
{
public:
	int speedX;
	int speedY;
	bool exists = true;
	sf::CircleShape ball;

	Ball(int radius, int windowWidth, int windowHeight, int platformWidth);
	bool isFallen(const sf::RectangleShape&);
	void respawn(int platformPositionX, int platformPositionY, int platformWidth);
	void move(float, int windowWidth, int windowHeight, sf::RectangleShape, std::vector<std::vector<Block>> &blocks);
	int getX();
	int getY();
	int getRadius();
	void putOnPlatform(const sf::RectangleShape& r);
};

