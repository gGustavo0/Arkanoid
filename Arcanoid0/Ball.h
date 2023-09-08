#pragma once

#include    <iostream>
#include    <vector>
#include    <SFML/Graphics.hpp>

using namespace std;

class Ball
{
public:
	int                speedX       = 200    ;
	int                speedY       = -200   ;
	bool               isSticked    = true   ;
	bool               toStick      = false  ;
	bool               exists       = true   ;
	sf::CircleShape    ball                  ;

	Ball(int platformPositionX, int platformPositionY, int radius = 10, int windowWidth = 800, int windowHeight = 800, int platformWidth = 150);

	bool    isFallen            (const sf::RectangleShape&)                                        ;
	void    moveWithPlatform    (const sf::RectangleShape&)                                        ;
	void    respawn             (int platformPositionX, int platformPositionY, int platformWidth)  ;
	void    move                (float)                                                            ;
	int     getX()                                                                                 ;
	void    stick(int, int)                                                                                ;
	int     getY()                                                                                 ;
	int     getRadius()                                                                            ;
	void    putOnPlatform       (const sf::RectangleShape& r)                                      ;
};

