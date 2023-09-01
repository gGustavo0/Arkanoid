#include "Physics.h"

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
	if (b.getPosition().x - b.getRadius() <= 0 || b.getPosition().x + b.getRadius() >= window.getSize().y)
		ball.speedX *= -1;
	if (b.getPosition().y - b.getRadius() <= 0)
		ball.speedY *= -1;
}

void Physics::platformBallCollision(Ball& ball, Platform& platform) {
	sf::CircleShape b = ball.ball;
	sf::RectangleShape p = platform.platform;
	if (intersects(b, p))
		//speedY *= -abs((platform.getPosition().x - ball.getPosition().x) / platform.getSize().x );
		ball.speedY *= -1;
	else
		if (b.getPosition().y >= p.getPosition().y)
			ball.exists = false;
}

void Physics::ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float elapsed) {
	sf::CircleShape b = ball.ball;
	b.setPosition(sf::Vector2f(b.getPosition().x + elapsed * 5 * ball.speedX, b.getPosition().y + elapsed* 5 * ball.speedY));
	for (auto& i : blocks)
	{
		for (auto& j : i)
		{
			if (intersects(b, j.block)) {
				if (j.exists()) {
					j.getHit();
					Side s = side(ball, j);
					if (s == Side::VERTICAL) {
						//speedX *= -1;
						ball.speedY *= -1;
						return;
					}
					if (s == Side::HORIZONTAL) {
						ball.speedX *= -1;
						return;
						//std::cout << speedY << std::endl;
					}
					if (s == Side::CORNER) {
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

void Physics::checkCollisions(Ball& ball, vector<vector<Block>>& blocks, Platform& platform, sf::RenderWindow& window, float elapsed) {
	platformBallCollision(ball, platform);
	ballBlocksCollision(ball, blocks, elapsed);
	ballScreenCollision(ball, window);
}
