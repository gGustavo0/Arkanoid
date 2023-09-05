#include "Ball.h"
#include <iostream>

Ball::Ball(int platformPosition, int platformPositionY, int radius, int windowWidth, int windowHeight, int platformWidth){
	ball = *new sf::CircleShape(radius);
	ball.setPosition(platformPosition + platformWidth / 2, platformPositionY - radius * 2);
	speedX = 0;
	speedY = 0;
}

void Ball::stick() {
	speedX = 0;
	speedY = 0;
}

void Ball::moveWithPlatform(const sf::RectangleShape& r) {
	//cout << ball.getPosition().x << endl;
	if (isSticked)
		ball.setPosition(sf::Vector2f(r.getPosition().x + r.getSize().x / 2 - ball.getRadius(), r.getPosition().y - ball.getRadius() * 2));
}
bool Ball::isFallen(const sf::RectangleShape& r) {
	return ball.getPosition().y >= r.getPosition().y;
}

void Ball::move(float elapsed) {
	ball.move(speedX * elapsed, speedY * elapsed);
}

int Ball::getX() {
	return ball.getPosition().x;
}

int Ball::getY() {
	return ball.getPosition().y;
}

int Ball::getRadius() {
	return ball.getRadius();
}

void Ball::putOnPlatform(const sf::RectangleShape& r) {
	
}
