#include "Counter.h"

Counter::Counter() {
	if (!font.loadFromFile("Roboto-LightItalic.ttf")) exit(-7);

	gameOver      .setFont(font);
	pointsText    .setFont(font);
	win           .setFont(font);

	gameOver      .setString(GAME_OVER);
	pointsText    .setString(POINTS + std::to_string(points));
	win           .setString(WIN);

	gameOver      .setCharacterSize(50);
	win           .setCharacterSize(50);
	pointsText    .setCharacterSize(25);

	gameOver      .setFillColor(sf::Color::Red);
	win           .setFillColor(sf::Color::Red);
	pointsText    .setFillColor(sf::Color::Blue);

	pointsText    .setPosition(650                                          , 10);
	win           .setPosition(400 - win.getLocalBounds().width / 2         , 400 - win.getLocalBounds().height / 2);
	gameOver      .setPosition(400 - gameOver.getLocalBounds().width / 2    , 400 - gameOver.getLocalBounds().width / 2);
}

sf::Text& Counter::getGameOver() {
	return gameOver;
}

sf::Text& Counter::getWin() {
	return win;
}

sf::Text& Counter::getPoints() {
	return pointsText;
}

void Counter::plusPoint() {
	points++;
	pointsText.setString(POINTS + std::to_string(points));
}

void Counter::minusPoints() {
	points -= 10;
	pointsText.setString(POINTS + std::to_string(points));
}

bool Counter::ifWin() const {
	return points >= 30;
}

bool Counter::ifGameOver() const{
	return points <= 0;
}
