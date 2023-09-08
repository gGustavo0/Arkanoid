#pragma once

#include                    <SFML/Graphics.hpp>

class Platform
{
public:
	int                   speed           = 8000   ;
	bool                  isFloor         = false  ;
	bool                  spawnNewBall    = false  ;
	sf::RectangleShape    platform                 ;

	Platform(int width, int heigth, int windowWidth, int windowHeight);
	
	void    move         (float, int windowWidth)  ;
	int     getX         ()                        ;
	int     getY         ()                        ;                       
	int     getWidth     ()                        ;
	int     getHeight    ()                        ;
};

