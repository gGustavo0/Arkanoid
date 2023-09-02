#pragma once


#include <vector>

#include                           <SFML/Graphics.hpp>
using namespace std;

class Ball
{
public:
	int speedX;
	int speedY;
	bool isSticked = true;
	bool toStick = false;
	bool exists = true;
	sf::CircleShape ball;

	Ball(int radius, int windowWidth, int windowHeight, int platformWidth);
	bool isFallen(const sf::RectangleShape&);
	void moveWithPlatform(int, float);
	void respawn(int platformPositionX, int platformPositionY, int platformWidth);
	void move(float);
	int getX();
	void stick();
	int getY();
	int getRadius();
	void putOnPlatform(const sf::RectangleShape& r);
};

