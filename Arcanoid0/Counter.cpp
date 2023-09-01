#include "Counter.h"

Counter::Counter() {
	if (!font.loadFromFile("Roboto-LightItalic.ttf"))
	{
		// error...
	}
	gameOver.setFont(font);
	pointsText.setFont(font);
	win.setFont(font);
	gameOver.setString(GAME_OVER);
	pointsText.setString(POINTS);
	win.setString(WIN);
	gameOver.setCharacterSize(50);
	win.setCharacterSize(50);
	pointsText.setCharacterSize(25);
	gameOver.setFillColor(sf::Color::Red);
	win.setFillColor(sf::Color::Red);
	pointsText.setFillColor(sf::Color::Blue);
	pointsText.setPosition(700, 10);
}

sf::Text& Counter::getGameOver() {
	return gameOver;
}

sf::Text& Counter::getPoints() {
	return pointsText;
}

void Counter::plusPoint() {
	points++;
}

void Counter::minusPoints() {
	points--;
}

bool Counter::ifGameOver() {
	return points == 0;
}
