#include "Counter.h"
#include <iostream>
#include <string>

Counter::Counter() {
	if (!font.loadFromFile("Roboto-LightItalic.ttf"))
	{
		// error...
	}
	gameOver.setFont(font);
	pointsText.setFont(font);
	win.setFont(font);
	gameOver.setString(GAME_OVER);
	pointsText.setString(POINTS + std::to_string(points));
	win.setString(WIN);
	gameOver.setCharacterSize(50);
	win.setCharacterSize(50);
	pointsText.setCharacterSize(25);
	gameOver.setFillColor(sf::Color::Red);
	win.setFillColor(sf::Color::Red);
	pointsText.setFillColor(sf::Color::Blue);
	pointsText.setPosition(700, 10);
	gameOver.setPosition(400 - gameOver.getLocalBounds().width / 2, 400 - gameOver.getLocalBounds().width / 2);
}

sf::Text& Counter::getGameOver() {
	return gameOver;
}

sf::Text& Counter::getPoints() {
	return pointsText;
}

void Counter::plusPoint() {
	pointsText.setString(POINTS + std::to_string(points));
	points++;
}

void Counter::minusPoints() {
	pointsText.setString(POINTS + std::to_string(points));
	points--;
}

bool Counter::ifGameOver() {
	return points == 0;
}
