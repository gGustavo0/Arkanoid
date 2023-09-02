#include "Physics.h"
#include <iostream>

bool Physics::intersects(sf::Shape& a, sf::Shape& b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

Side Physics::side(Ball& ball, Block& block) {
	sf::RectangleShape r = block.block;
	sf::CircleShape b = ball.ball;
	if (
		(b.getPosition().x + b.getRadius() <= r.getPosition().x && b.getPosition().y + b.getRadius() <= r.getPosition().y)
		|| (b.getPosition().x + b.getRadius() <= r.getPosition().x && b.getPosition().y - b.getRadius() >= r.getPosition().y + r.getSize().y)
		|| (b.getPosition().x - b.getRadius() >= r.getPosition().x + r.getSize().x && b.getPosition().y + b.getRadius() <= r.getPosition().y)
		|| (b.getPosition().x - b.getRadius() >= r.getPosition().x + r.getSize().x && b.getPosition().y + b.getRadius() >= r.getPosition().y + r.getSize().y)
		) return Side::CORNER;
	if (
		b.getPosition().y + b.getRadius() <= r.getPosition().y
		|| b.getPosition().y - b.getRadius() >= r.getPosition().y + r.getSize().y
		) return Side::HORIZONTAL;
	return Side::VERTICAL;
}

void Physics::ballScreenCollision(Ball& ball, sf::RenderWindow& window) {
	sf::CircleShape b = ball.ball;
	if (b.getPosition().x - b.getRadius() <= 0 || b.getPosition().x + b.getRadius() >= window.getSize().x)
		ball.speedX *= -1;
	if (b.getPosition().y - b.getRadius() <= 0 || b.getPosition().y + b.getRadius() >= window.getSize().y)
		ball.speedY *= -1;
}

void Physics::platformBallCollision(Ball& ball, Platform& platform, Counter& counter, sf::RenderWindow& window) {
	sf::CircleShape b = ball.ball;
	sf::RectangleShape p = platform.platform;
	if (intersects(b, p)) {
		//speedY *= -abs((platform.getPosition().x - ball.getPosition().x) / platform.getSize().x );
		if (ball.toStick) {
			ball.stick();
			ball.isSticked = true;
			ball.toStick = false;
		} else 
			ball.speedY *= -1;
	}
	else {
		if (isFloor)
		{
			isFloor = false;
			return;
		}
		if (b.getPosition().y >= p.getPosition().y) {
			ball.exists = false;
			counter.minusPoints();
		}
	}
}

void Physics::bonusPlatformCollision(Bonus& bonus, Platform& platform) {
	sf::RectangleShape b = bonus.bonus;
	sf::RectangleShape p = platform.platform;
	if (intersects(b, p)) {
		delete(&bonus);
	}
}

void Physics::ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float elapsed, Counter& counter) {
	sf::CircleShape b = ball.ball;
	b.setPosition(sf::Vector2f(b.getPosition().x + elapsed * 5 * ball.speedX, b.getPosition().y + elapsed* 5 * ball.speedY));
	for (auto& i : blocks)
	{
		for (auto& j : i)
		{
			if (intersects(b, j.block)) {
				if (j.exists()) {
					j.getHit(counter);
					Side s = side(ball, j);
					if (s == Side::VERTICAL) {
						std::cout << "VERTICAL" << std::endl;
						ball.speedY *= -1;
						return;
					}
					if (s == Side::HORIZONTAL) {
						ball.speedX *= -1;
						return;
						std::cout << "HORIZONTAL" << std::endl;
					}
					if (s == Side::CORNER) {
						std::cout << "CORNER" << std::endl;
						ball.speedY *= -1;
						ball.speedX *= -1;
						return;
						//speedX *= -1;
					}
				}
			}
		}
	}
	b.setPosition(sf::Vector2f(b.getPosition().x - elapsed * 5* ball.speedX, b.getPosition().y - elapsed *5* ball.speedY));
}

void Physics::checkCollisions(Ball& ball, vector<vector<Block>>& blocks, Platform& platform, sf::RenderWindow& window, float elapsed, Counter& counter) {
	platformBallCollision(ball, platform, counter, window);
	ballBlocksCollision(ball, blocks, elapsed, counter);
	ballScreenCollision(ball, window);
}
