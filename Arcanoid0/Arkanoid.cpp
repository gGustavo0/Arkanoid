#include "Arkanoid.h"
#include <iostream>

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
	blocksCount = 14 * 4;
	blocks.resize(14);
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 4; j++) {
			blocks[i].push_back(*new Block(50 + 50 * i, 50 + 50 * j, 50));
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				platform.move(-elapsed.asSeconds(), window->getSize().x);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				platform.move(elapsed.asSeconds(), window->getSize().x);
			
		}
		if (counter.ifGameOver()) {
			window->draw(counter.getGameOver());
		}
		else {
			for (auto& ball : balls) {
				physics.checkCollisions(ball, blocks, platform, *window, elapsed.asSeconds());
				ball.move(elapsed.asSeconds(), window->getSize().x, window->getSize().y, platform.platform, blocks);
			}
			window->clear(sf::Color::Black);
			window->draw(platform.platform);
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