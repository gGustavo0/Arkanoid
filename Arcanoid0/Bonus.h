#pragma once
#include                           <SFML/Graphics.hpp>
#include "Platform.h"
#include "Ball.h"

class Bonus
{
public:
	int speed = 50;
	sf::RectangleShape bonus;
	Bonus(sf::Vector2f);
	void move(float);
};

