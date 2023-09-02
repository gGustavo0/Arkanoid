#include "Bonus.h"

Bonus::Bonus(sf::Vector2f position): bonus(*new sf::RectangleShape(sf::Vector2f(40, 20))){
	bonus.setPosition(position);
}


void Bonus::move(float elapsed) {
	bonus.move(0, speed * elapsed);
}