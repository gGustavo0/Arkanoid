#include "Platform.h"

Platform::Platform(int width, int height, int windowWidth, int windowHeigth){
	platform = *new sf::RectangleShape(sf::Vector2f(width, height));
	platform.setPosition((windowWidth / 2) - (width / 2) + 10 / 2, windowHeigth * 0.95);
	speed = 8000;
};

void Platform::move(float elapsed, int windowWidth) {
	if (platform.getPosition().x <= 0 && elapsed < 0) return;
	if (platform.getPosition().x + platform.getSize().x >= windowWidth && elapsed > 0) return;
	platform.move(speed * elapsed, 0.0);
}

int Platform::getHeight() {
	return platform.getSize().y;
}

int Platform::getWidth() {
	return platform.getSize().x;
}

int Platform::getX() {
	return platform.getPosition().x;
}

int Platform::getY() {
	return platform.getPosition().y;
}