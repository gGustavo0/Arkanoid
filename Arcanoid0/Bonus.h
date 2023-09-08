#pragma once
#include    <SFML/Graphics.hpp>
#include    "Platform.h"
#include    "Ball.h"

class Bonus
{
public:

	Bonus(sf::Vector2f);

	virtual void                   destroy     ()                ;
	        int                    getSpeed    ()         const  ;
	        void                   move        (float)           ;
			sf::RectangleShape&    getBonus    ()                ;
			 
	friend bool operator == (const Bonus& b, const Bonus& t);
	friend bool operator != (const Bonus& b, const Bonus& t);
	
private:
	int                   speed = 100;
	sf::RectangleShape    bonus;
};

