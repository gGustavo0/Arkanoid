#include "Arkanoid.h"



Arkanoid::Arkanoid(int windowWidth, int windowHeight, string title, int platformWidth
	, int platformHeight, int ballRadius, int platformPositionX, int platformPositionY) :

	window(new sf::RenderWindow(sf::VideoMode(windowHeight, windowWidth), title, sf::Style::Close)),
	platform(*new Platform(platformWidth, platformHeight, windowWidth, windowHeight)),
	counter(*new Counter()),
	physics(*new Physics())
{
	balls.push_back(*new Ball(platform.getPosition().x, platform.getPosition().y));
}

bool Arkanoid::checkPoints() {
	if (counter.ifWin()) { 
		window->clear(sf::Color::Black);
		window->draw(counter.getWin()); 
		return true;
	} else 
		if (counter.ifGameOver()) {
			window->clear(sf::Color::Black);
			window->draw(counter.getGameOver()); 
			return true;
		}
	return false;
}

void Arkanoid::handleEvents(float elapsed) {
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			platform.move(-elapsed, window->getSize().x);
			for (auto& ball : balls) ball.moveWithPlatform(platform.getPlatform());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			platform.move(elapsed, window->getSize().x);
			for (auto& ball : balls) ball.moveWithPlatform(platform.getPlatform());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
			for (auto& ball : balls)
				for (auto& ball : balls)
					if (ball.isSticked) {
						ball.setSpeedX(START_SPEED);
						ball.setSpeedY(- START_SPEED);
						ball.isSticked = false;
					}
	}
}

void Arkanoid::moveBonuses(float elapsed) {
	for (auto& bonus : bonuses){
		bonus->move(elapsed);
		window->draw(bonus->getBonus());
	}
}

void Arkanoid::createBlocks() {
	srand(time(0));
	blocks.resize(14);
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 4; j++) blocks[i].push_back(*new Block(BLOCK_SIZE + BLOCK_SIZE * i, BLOCK_SIZE + BLOCK_SIZE * j, bonuses, BLOCK_SIZE));
}

void Arkanoid::checkBonuses() {
	auto li = bonuses.begin();
	while (li != bonuses.end()) {
		if (li == bonuses.end()) break;
		if (physics.bonusPlatformCollision((*li)->getBonus(), platform)) {
			(*li)->destroy();
			Bonus* temp = (*li);
			li = bonuses.erase(li);
			delete(temp);
			continue;
		}

		if (physics.screenBonusCollision((*li)->getBonus(), *window))
		{
			Bonus* temp = (*li);
			li = bonuses.erase(li);
			delete(temp);
			continue;
		}
		li++;
	}
}

void Arkanoid::moveBalls(float elapsed) {
	for (auto& ball : balls) ball.move(elapsed);
}

void Arkanoid::drawBalls() {
	for (auto ball = balls.begin(); ball != balls.end();) {
		if (ball == balls.end()) break;
		if ((*ball).exists) {
			window->draw((*ball).getBall());
			ball++;
		}
		else
			ball = balls.erase(ball);
	}
}

void Arkanoid::drawBlocks() {
	for (auto& i : blocks)
		for (auto& j : i)
			if (j.exists()) window->draw(j.getBlock());
}

void Arkanoid::start() {
	createBlocks();
	sf::Clock clock;
	while (window->isOpen())
	{
		sf::Time  elapsed = clock.restart();

		handleEvents(elapsed.asSeconds());
		if (!checkPoints()) {
			moveBalls(elapsed.asSeconds());
			physics.checkCollisions(balls, blocks, platform, *window, elapsed.asSeconds(), counter);
			drawAll();
			if (!counter.ifGameOver() && balls.size() == 0) balls.push_back(*new Ball(platform.getPosition().x, platform.getPosition().y));
			drawBalls();
			drawBlocks();
			checkBonuses();
			moveBonuses(elapsed.asSeconds());

			if (platform.spawnNewBall) {
				balls.push_back(*new Ball(platform.getPosition().x, platform.getPosition().y));
				platform.spawnNewBall = false;
			}
			window->draw(counter.getPoints());
		}
		window->display();
	}

}

void Arkanoid::drawAll() {
	window->clear(sf::Color::Black);
	window->draw(platform.getPlatform());
	window->draw(counter.getPoints());
}