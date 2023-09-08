#pragma once

#define POINTS       "points: "
#define GAME_OVER    "GAME OVER!"
#define WIN          "YOU WIN"

#include             <SFML/Graphics.hpp>
#include             <iostream>
#include             <string>

class Counter
{
public:
	Counter();

	int              points        = 1  ;

	sf::Font         font               ;
	sf::Text         pointsText         ;
	sf::Text         gameOver           ;
	sf::Text         win                ;

	sf::Text&        getGameOver()      ;
	sf::Text&        getPoints()        ;
	sf::Text&        getWin()           ;
	void             plusPoint()        ;
	void             minusPoints()      ;
	bool             ifGameOver()       ;
};
