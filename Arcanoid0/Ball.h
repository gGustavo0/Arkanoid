#pragma once

#include                           <iostream>
#include                           <vector>
#include                           <SFML/Graphics.hpp>

using namespace std;

class Ball
{
public:
	bool               isSticked    = true   ;
	bool               toStick      = false  ;
	bool               exists       = true   ;

	Ball(int platformPositionX, int platformPositionY, int radius = 10, int windowWidth = 800, int windowHeight = 800, int platformWidth = 150);
	  
	bool                isFallen            (const sf::RectangleShape&)      const  ;
	void                moveWithPlatform    (const sf::RectangleShape&)             ;
	void                move                (float)                                 ;
	void                stick(int, int)                                             ;
	int                 getRadius()                                          const  ;
	void                putOnPlatform       (const sf::RectangleShape&)             ;
	void                setPosition         (int, int)                              ;
	sf::Vector2f        getPosition         ()                               const  ;
	sf::Vector2i        getSpeed            ()                               const  ;
	void                setSpeedX           (int)                                   ;
	void                setSpeedY           (int)                                   ;
	sf::CircleShape&    getBall             ()                                      ;
	void                changeSpeed         (int, int)                              ;
	void                reverseSpeedX       ()                                      ;
	void                reverseSpeedY       ()                                      ;

private:
	sf::CircleShape    ball;

	int                speedX = 200;
	int                speedY = -200;
};

