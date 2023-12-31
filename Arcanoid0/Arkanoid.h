#pragma once

#include                           "Platform.h"
#include                           "Block.h"
#include                           "Ball.h"
#include                           "Counter.h"
#include                           "Physics.h"
#include                           "Bonus.h"
#include                           "Bonuses.h"

#include                           <list>
#include                           <iostream>
#include                           <ctime>
#include                           <cstdlib>
#include                           <SFML/Graphics.hpp>
#include                           <string>
#include                           <memory>

#define START_SPEED                200
#define WINDOW_HEIGTH              800
#define WINDOW_WIDTH               800
#define PLATFORM_HEIGTH            20
#define PLATFORM_WIDTH             150
#define BALL_RADIUS                10
#define PLATFORM_POSITION_X        300
#define PLATFORM_POSITION_Y        600
#define NUMBER_OF_BLOCKS_X         10
#define NUMBER_OF_BLOCKS_y         5
#define BLOCK_SIZE                 50
#define TITLE                      "ARKANOID"

using namespace std;

class Arkanoid
{
public:
	Arkanoid(int windowWidth = WINDOW_WIDTH, int windowHeight = WINDOW_HEIGTH, string title = TITLE
		, int platformWidth = PLATFORM_WIDTH, int platformHeight = PLATFORM_HEIGTH, int ballRadius = BALL_RADIUS
		, int platformPositionX = PLATFORM_POSITION_X, int platformPositionY = PLATFORM_POSITION_Y);

	~Arkanoid();

	void start();
private:
	unique_ptr<sf::RenderWindow>        window       ;
	Platform                            platform     ;
	Counter                             counter      ;
	vector<vector<Block>>               blocks       ;
	list<Ball>                          balls        ;
	list<Bonus*>                        bonuses      ;
	Physics                             physics      ;
	
	void drawAll       ()       ;
	void createBlocks  ()       ;
	bool checkPoints   ()       ;
	void checkBonuses  ()       ;
	void drawBalls     ()       ;
	void drawBlocks    ()       ;
	void handleEvents  (float)  ;
	void moveBonuses   (float)  ;
	void moveBalls     (float)  ;
};


