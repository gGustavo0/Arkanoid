#pragma once
#include                           <SFML/Graphics.hpp>
#include "Platform.h"
#include "Ball.h"

class Bonus
{
public:
	int speed = 100;
	sf::RectangleShape bonus;
	Bonus(sf::Vector2f);
	virtual void destroy();
	void move(float);
	friend bool operator == (const Bonus& b, const Bonus& t);
	friend bool operator != (const Bonus& b, const Bonus& t);
};

