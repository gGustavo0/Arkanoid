#include "Physics.h"
#include <iostream>

bool Physics::intersects(sf::Shape& a, sf::Shape& b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

Side Physics::side(Ball& ball, sf::RectangleShape& r) {
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

void Physics::ballScreenCollision(Ball& ball, sf::RenderWindow& window, Counter &counter, Platform& platform) {
	sf::CircleShape b = ball.ball;
	if (b.getPosition().x - b.getRadius() <= 0 || b.getPosition().x + b.getRadius() >= window.getSize().x)
		ball.speedX *= -1;
	if (b.getPosition().y - b.getRadius() <= 0)
		ball.speedY *= -1;
	if (b.getPosition().y + b.getRadius() >= window.getSize().y) {
		if (platform.isFloor) {
			ball.speedY *= -1;
			platform.isFloor = false;
		}
		else {
			ball.exists = false;
			counter.minusPoints();
		}
	}
}

void Physics::platformBallCollision(Ball& ball, Platform& platform, Counter& counter, sf::RenderWindow& window, float elapsed) {
	sf::CircleShape b = ball.ball;
	sf::RectangleShape p = platform.platform;
	if (intersects(b, p)) {
		//speedY *= -abs((platform.getPosition().x - ball.getPosition().x) / platform.getSize().x );
		cout << ball.toStick << endl;
		if (ball.toStick) {
			ball.stick();
			ball.isSticked = true;
			ball.toStick = false;
		}
		else {
			if (side(ball, platform.platform) == Side::HORIZONTAL)
			{
				ball.ball.setPosition(sf::Vector2f(ball.ball.getPosition().x, platform.platform.getPosition().y - platform.platform.getSize().y));
				ball.speedY *= -1;
			}
			else {
				int vec = ball.speedX > 0;
				ball.ball.setPosition(sf::Vector2f(platform.platform.getPosition().x + !vec * platform.platform.getSize().x - vec * ball.ball.getRadius(), ball.ball.getPosition().y));
				ball.speedX *= -1;
				ball.speedY *= -1;
			}
		}
	}
}

bool Physics::screenBonusCollision(sf::RectangleShape bonus, sf::RenderWindow& window) {
	sf::RectangleShape b = bonus;
	if (b.getPosition().y + b.getSize().y >= window.getSize().y)
	{
		return true;
	}
	return false;
}

bool Physics::bonusPlatformCollision(sf::RectangleShape bonus, Platform& platform) {
	sf::RectangleShape b = bonus;
	sf::RectangleShape p = platform.platform;
	//cout << bonus.getSize().x << endl;
	if (intersects(b, p)) {
		return true;
	}
	return false;
}

void Physics::ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float elapsed, Counter& counter, Platform& platform) {
	sf::CircleShape b = ball.ball;
	b.setPosition(sf::Vector2f(b.getPosition().x + elapsed * 5 * ball.speedX, b.getPosition().y + elapsed* 5 * ball.speedY));
	for (auto& i : blocks)
	{
		for (auto& j : i)
		{
			if (intersects(b, j.block)) {
				if (j.exists()) {
					j.getHit(counter, ball , platform);
					Side s = side(ball, j.block);
					if (s == Side::VERTICAL) {
						int vec = ball.speedY < 0;
						ball.ball.setPosition(sf::Vector2f(ball.ball.getPosition().x, j.block.getPosition().y + j.block.getSize().y * vec - !vec * ball.getRadius()));
						//std::cout << "VERTICAL" << std::endl;
						ball.speedY *= -1;
						return;
					}
					if (s == Side::HORIZONTAL) {
						int vec = ball.speedX < 0;
						ball.ball.setPosition(sf::Vector2f(j.block.getPosition().x + j.block.getSize().x * vec - !vec * ball.getRadius(), ball.ball.getPosition().y));
						ball.speedX *= -1;
						return;
						//std::cout << "HORIZONTAL" << std::endl;
					}
					if (s == Side::CORNER) {
						//std::cout << "CORNER" << std::endl;
						int vecX = ball.speedX < 0;
						int vecY = ball.speedY < 0;
						ball.ball.setPosition(sf::Vector2f(j.block.getPosition().x + j.block.getSize().x * vecX - !vecX * ball.getRadius(),
							j.block.getPosition().y + j.block.getSize().y * vecY - !vecY * ball.getRadius()));
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
	platformBallCollision(ball, platform, counter, window, elapsed);
	ballBlocksCollision(ball, blocks, elapsed, counter, platform);
	ballScreenCollision(ball, window, counter, platform);
}
