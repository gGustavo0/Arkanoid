#pragma once

#include                    <SFML/Graphics.hpp>

class Platform
{
private:
	int                   speed = 8000;
	sf::RectangleShape    platform;
public:
	
	bool                  isFloor         = false  ;
	bool                  spawnNewBall    = false  ;

	Platform(int width, int heigth, int windowWidth, int windowHeight);
	
	void                   setSize        (int, int)                         ;
	void                   move           (float, int windowWidth)           ;
	sf::Vector2f           getPosition    ()                          const  ;
	sf::Vector2f           getSize        ()                          const  ;
	sf::RectangleShape&    getPlatform    ()                                 ;
};

