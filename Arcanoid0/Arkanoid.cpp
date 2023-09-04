#include "Arkanoid.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Arkanoid::Arkanoid(int windowWidth, int windowHeight, string title, int platformWidth
	, int platformHeight, int ballRadius, int platformPositionX, int platformPositionY) :

	window(new sf::RenderWindow(sf::VideoMode(windowHeight, windowWidth), title, sf::Style::Close)),
	platform(*new Platform(platformWidth, platformHeight, windowWidth, windowHeight)),
	ball(*new Ball(ballRadius, windowWidth, windowHeight, platformWidth)),
	counter(*new Counter()),
	physics(*new Physics())
{
	balls.push_back(ball);
}

void Arkanoid::createBlocks() {
	srand(time(0));
	blocksCount = 14 * 4;
	blocks.resize(14);
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 4; j++) {
			blocks[i].push_back(*new Block(50 + 50 * i, 50 + 50 * j, bonuses, 50));
		}
	}
}

void Arkanoid::start() {
	createBlocks();
	sf::Clock clock;
	while (window->isOpen())
	{
		sf::Event event;
		sf::Time elapsed = clock.restart();
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ 
				//cout << platform.platform.getPosition().x << endl;
				platform.move(-elapsed.asSeconds(), window->getSize().x);
				for (auto& ball : balls) 
					ball.moveWithPlatform(platform.speed, -elapsed.asSeconds());
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				//cout << platform.platform.getPosition().x << endl;
				platform.move(elapsed.asSeconds(), window->getSize().x);
				for (auto& ball : balls) 
					ball.moveWithPlatform(platform.speed, elapsed.asSeconds());
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				for (auto& ball : balls) {
					for (auto& ball : balls) {
						ball.speedX = 200;
						ball.speedY = -200;
						ball.isSticked = false;
					}
				}
				
			}
				
			
		}
		if (counter.ifGameOver()) {
			window->draw(counter.getGameOver());
		}
		else {
			for (auto& ball : balls) {
				physics.checkCollisions(ball, blocks, platform, *window, elapsed.asSeconds(), counter);
				ball.move(elapsed.asSeconds());
			}
			window->clear(sf::Color::Black);
			window->draw(platform.platform);
			window->draw(counter.getPoints());
			if (counter.points == 0)
			{
				window->clear(sf::Color::Black);
				window->draw(counter.getGameOver());
				//break;
			} else {
			
			}
			for (auto& ball : balls) {
				if (ball.exists)
					window->draw(ball.ball);
				else
				{
					swap(ball, balls.back());
					balls.pop_back();
					delete(&ball);
					//remove
				}
			}
			for (auto& i: blocks) {
				for (auto& j : i) {
					if (j.exists()) {
						window->draw(j.block);
					}
					else {
						//remove
					}
				}
			}
			for (auto bonus : bonuses)
			{
				//cout << "ARC" << endl;
				//cout << bonuses.size() << endl;
					if (physics.bonusPlatformCollision(bonus->bonus, platform)) {
						bonus->destroy();
						//bonuses.remove(bonus);
						cout << "AAAA" << endl;
						//delete(&bonus);
						continue;
					}
					if (physics.screenBonusCollision(bonus->bonus, *window))
					{
						//bonuses.remove(bonus);
						//delete(&bonus);
						continue;
					}
			}
			for (auto& bonus: bonuses) 
			{
				bonus->move(elapsed.asSeconds());
				window->draw(bonus->bonus);
			}
			if (platform.spawnNewBall)
				balls.push_back(*new Ball());
			window->draw(counter.getPoints());
			window->display();
		}
	}
}

void Arkanoid::drawAll() {
	for (auto& i : blocks) {
		for (auto& j : i) {
			window->draw(j.block);
		}
	}
	for (auto& ball : balls) {
		if(ball.exists)
			window->draw(ball.ball);
		else
		{
			//remove
		}
	}
	window->draw(platform.platform);
	window->draw(ball.ball);
	window->draw(counter.getPoints());

}