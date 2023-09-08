#include "Platform.h"

Platform::Platform(int width, int height, int windowWidth, int windowHeigth){
	platform = *new sf::RectangleShape(sf::Vector2f(width, height));
	platform.setPosition((windowWidth / 2) - (width / 2) + 10 / 2, windowHeigth * 0.95);
};

void Platform::move(float elapsed, int windowWidth) {
	if (platform.getPosition().x <= 0 && elapsed < 0) {
		platform.setPosition(0, platform.getPosition().y);
		return;
	}
	if (platform.getPosition().x + platform.getSize().x >= windowWidth && elapsed > 0) {
		platform.setPosition(windowWidth - platform.getSize().x, platform.getPosition().y);
		return;
	}
	platform.move(speed * elapsed, 0.0);
}

void Platform::setSize(int x, int y) {
	platform.setSize(sf::Vector2f(x, y));
}

sf::Vector2f Platform::getSize() const {
	return platform.getSize();
}

sf::Vector2f Platform::getPosition() const {
	return platform.getPosition();
}

sf::RectangleShape& Platform::getPlatform() {
	return platform;
}
