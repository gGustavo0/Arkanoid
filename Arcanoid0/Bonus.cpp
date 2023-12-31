#include    "Bonus.h"
#include    <iostream>

Bonus::Bonus(sf::Vector2f position): bonus(*new sf::RectangleShape(sf::Vector2f(40, 20))){
	bonus.setPosition(position);
}

int Bonus::getSpeed() const {
	return speed;
}

sf::RectangleShape& Bonus::getBonus() {
	return bonus;
}

void Bonus::destroy() {}

void Bonus::move(float elapsed) {
	bonus.move(0, speed * elapsed);
}

bool operator == (const Bonus& b, const Bonus& t) {
	if (b.bonus.getPosition().y == t.bonus.getPosition().y && b.bonus.getPosition().x == t.bonus.getPosition().x) return true;
	return false;
}
bool operator != (const Bonus& b, const Bonus& t) {
	if (b.bonus.getPosition().y != t.bonus.getPosition().y && b.bonus.getPosition().x != t.bonus.getPosition().x) return true;
	return false;
}