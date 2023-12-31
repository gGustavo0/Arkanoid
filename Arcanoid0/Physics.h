#pragma once

#include    "Ball.h"
#include    "Counter.h"
#include    "Block.h"
#include    "Bonus.h"
#include    "Bonuses.h"
#include    "Platform.h"

#include    <vector>
#include    <list>
#include    <SFML/Graphics.hpp>

using namespace std;

enum class Side {
	HORIZONTAL,
	HORIZONTAL_LEFT,
	VERTICAL,
	VERTICAL_FLOOR,
	CORNER,
	CORNER_RIGHT_TOP,
	CORNER_LEFT_TOP,
};

class Physics
{
public:
	Side    side                      (Ball&ball, sf::RectangleShape&)                                                                            ;
	Side    side(Ball&, Ball&);
	void    ballBallCollision(list<Ball>& balls);
	bool    screenBonusCollision      (sf::RectangleShape bonus, sf::RenderWindow&)                                                               ;
	void    ballScreenCollision       (Ball& ball, sf::RenderWindow& window, Counter&, Platform&)                                                 ;
	bool    bonusPlatformCollision    (sf::RectangleShape bonus, Platform& platform)                                                              ;
	void    platformBallCollision     (Ball& ball, Platform& platform, Counter&, sf::RenderWindow&, float)                                        ;
	void    ballBlocksCollision       (Ball& ball, vector<vector<Block>>& blocks, float, Counter&, Platform&)                                     ;
	void    checkCollisions           (list<Ball>& balls, vector<vector<Block>> &blocks, Platform &platform, sf::RenderWindow& window, float, Counter&)  ;
	bool    intersects                (sf::Shape&, sf::Shape&)                                                                                    ;
};

