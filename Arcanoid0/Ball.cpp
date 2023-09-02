#include "Ball.h"
#include <iostream>

Ball::Ball(int radius, int windowWidth, int windowHeight, int platformWidth){
	ball = *new sf::CircleShape(radius);
	ball.setPosition(windowWidth / 2, windowHeight * 0.95 - 2 * radius);
	speedX = 0;
	speedY = 0;
}

void Ball::stick() {
	speedX = 0;
	speedY = 0;
}

void Ball::moveWithPlatform(int speed, float elapsed) {
	//cout << ball.getPosition().x << endl;
	if(isSticked)
		ball.move(speed * elapsed, 0);
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
