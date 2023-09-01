#include "Block.h"

Block::Block(int x, int y, int size): block(*new sf::RectangleShape(sf::Vector2f(size, size))) {
	block.setOutlineThickness(-5);
	block.setOutlineColor(sf::Color::Black);
	block.setPosition(sf::Vector2f(x, y));
}

void Block::getHit() {
	hp--;
}

bool Block::exists() {
	return hp > 0;
}