#pragma once

#include                    <SFML/Graphics.hpp>

class Platform
{
public:

	int speed = 8000;
	sf::RectangleShape    platform;

	Platform(int width, int heigth, int windowWidth, int windowHeight);
	
	void move(float, int windowWidth);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};

