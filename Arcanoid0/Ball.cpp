#include "Ball.h"
#include <iostream>

Ball::Ball(int radius, int windowWidth, int windowHeight, int platformWidth){
	ball = *new sf::CircleShape(radius);
	ball.setPosition(windowWidth / 2, windowHeight * 0.95 - 2 * radius);
	speedX =200;
	speedY = -200;
}

bool Ball::isFallen(const sf::RectangleShape& r) {
	return ball.getPosition().y >= r.getPosition().y;
}

void Ball::move(float elapsed, int windowWidth, int windowHeight, sf::RectangleShape platform, std::vector<std::vector<Block>> &blocks) {
	//одновременно пересекается с двумя плоками и меняет скорость дважды 
	
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
