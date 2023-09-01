#pragma once

#include                    <SFML/Graphics.hpp>

#define SIZE 50

class Block
{
public:
	int hp = 1;
	sf::RectangleShape    block;

	Block(int x, int y, int size = SIZE);
	
	void getHit();
	void bonus();
	bool exists();


};

