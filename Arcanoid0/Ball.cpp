#include "Ball.h"

Ball::Ball(int platformPosition, int platformPositionY, int radius, int windowWidth, int windowHeight, int platformWidth){
	ball      = *new sf::CircleShape(radius);
	speedX    = 0;
	speedY    = 0;
	ball.setPosition(platformPosition + platformWidth / 2 - radius, platformPositionY - radius * 2);
}

sf::Vector2f Ball::getPosition() const {
	return ball.getPosition();
}

void Ball::changeSpeed(int x, int y){
	speedX += x;
	speedY += y;
}

void Ball::reverseSpeedX() {
	speedX *= -1;
}

void Ball::reverseSpeedY() {
	speedY *= -1;
}

void Ball::setPosition(int x, int y) {
	ball.setPosition(x, y);
}

sf::CircleShape& Ball::getBall()  {
	return ball;
}


sf::Vector2i Ball::getSpeed() const {
	return sf::Vector2i(speedX, speedY);
}

void Ball::setSpeedX(int x) {
	speedX = x;
}
void Ball::setSpeedY(int y) {
	speedY = y;
}

void Ball::stick(int platformPositionX, int platformWidth) {
	ball.setPosition(platformPositionX + platformWidth / 2, ball.getPosition().y);
	speedX = 0;
	speedY = 0;
}

void Ball::moveWithPlatform(const sf::RectangleShape& r) {
	if (isSticked) ball.setPosition(sf::Vector2f(r.getPosition().x + r.getSize().x / 2 - ball.getRadius(), r.getPosition().y - ball.getRadius() * 2));
}
bool Ball::isFallen(const sf::RectangleShape& r) const{
	return ball.getPosition().y >= r.getPosition().y;
}

void Ball::move(float elapsed) {
	ball.move(speedX * elapsed, speedY * elapsed);
}

int Ball::getRadius() const {
	return ball.getRadius();
}

void Ball::putOnPlatform(const sf::RectangleShape& r) {
	
}
