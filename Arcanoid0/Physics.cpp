#include "Physics.h"

bool Physics::intersects(sf::Shape& a, sf::Shape& b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

Side Physics::side(Ball& ball, sf::RectangleShape& r) {
	auto cn = (r.getPosition() - r.getSize() / 2.f) - (ball.getPosition() - sf::Vector2f(ball.getRadius() / 2.f, ball.getRadius() / 2.f));
	sf::CircleShape b = ball.getBall();
	if (
		b.getPosition().y <= r.getPosition().y + r.getSize().y
		&& b.getPosition().y + b.getRadius() * 2 >= r.getPosition().y
		) return Side::HORIZONTAL;
	return Side::VERTICAL;
}

void Physics::ballScreenCollision(Ball& ball, sf::RenderWindow& window, Counter &counter, Platform& platform) {
	sf::CircleShape b = ball.getBall();
	if (b.getPosition().x - b.getRadius() <= 0 ) { 
		ball.setPosition(ball.getRadius(), ball.getPosition().y);
		ball.reverseSpeedX();
	}
	if (b.getPosition().x + b.getRadius() >= window.getSize().x)
	{
		ball.setPosition(window.getSize().x - ball.getRadius(), ball.getPosition().y);
		ball.reverseSpeedX();
	}
	if (b.getPosition().y - b.getRadius() <= 0) {
		ball.setPosition(ball.getPosition().x, ball.getRadius());
		ball.reverseSpeedY();
	}
	if (b.getPosition().y + b.getRadius() >= window.getSize().y) 
		if (platform.isFloor) {
			ball.setPosition(ball.getPosition().x, window.getSize().x - ball.getRadius() - ball.getRadius());
			ball.reverseSpeedY();
			platform.isFloor = false;
		}
		else {
			ball.exists = false;
			counter.minusPoints();
		}
}

void Physics::platformBallCollision(Ball& ball, Platform& platform, Counter& counter, sf::RenderWindow& window, float elapsed) {
	sf::CircleShape           b = ball.getBall();
	sf::RectangleShape        p = platform.getPlatform();

	if (intersects(b, p)) {
		if (ball.toStick) {
			ball.stick(platform.getPosition().x, platform.getSize().x);
			ball.setPosition(ball.getPosition().x, platform.getPosition().y - 2 * ball.getRadius());
			ball.isSticked    = true;
			ball.toStick      = false;
		}
		else 
			if (side(ball, platform.getPlatform()) == Side::HORIZONTAL)
			{
				ball.setPosition(ball.getPosition().x, platform.getPosition().y - platform.getSize().y - ball.getRadius() * 2);
				ball.reverseSpeedY();
			}
			else {
				int vec = ball.getSpeed().x > 0;
				ball.setPosition(platform.getPosition().x + !vec * platform.getSize().x - vec * ball.getRadius(), ball.getPosition().y);
				ball.reverseSpeedX();
				ball.reverseSpeedY();
			}
	}
}

bool Physics::screenBonusCollision(sf::RectangleShape bonus, sf::RenderWindow& window) {
	sf::RectangleShape b = bonus;
	if (b.getPosition().y + b.getSize().y >= window.getSize().y) return true;
	return false;
}

bool Physics::bonusPlatformCollision(sf::RectangleShape bonus, Platform& platform) {
	sf::RectangleShape b = bonus;
	sf::RectangleShape p = platform.getPlatform();

	if (intersects(b, p)) return true;
	return false;
}

void Physics::ballBlocksCollision(Ball& ball, vector<vector<Block>>& blocks, float elapsed, Counter& counter, Platform& platform) {
	sf::CircleShape b = ball.getBall();
	b.setPosition(sf::Vector2f(b.getPosition().x + elapsed * 5 * ball.getSpeed().x, b.getPosition().y + elapsed * 5 * ball.getSpeed().y));
	for (auto& i : blocks)
		for (auto& j : i)
		{
			if (intersects(b, j.getBlock())) {
				if (j.exists()) {
					j.getHit(counter, ball , platform);
					Side s = side(ball, j.getBlock());
					if (s == Side::VERTICAL) {
						bool vec = ball.getSpeed().y < 0;
						ball.setPosition(ball.getPosition().x, j.getPosition().y + j.getSize() * vec - !vec * ball.getRadius());
						ball.reverseSpeedY();
						return;
					}
					if (s == Side::HORIZONTAL) {
						bool vec = ball.getSpeed().x < 0;
						ball.setPosition(j.getPosition().x + j.getSize() * vec - !vec * ball.getRadius(), ball.getPosition().y);
						ball.reverseSpeedX();
						return;
					}
				}
			}
	}
	b.setPosition(sf::Vector2f(b.getPosition().x - elapsed * 5* ball.getSpeed().x, b.getPosition().y - elapsed * 5 * ball.getSpeed().y));
}
Side Physics::side(Ball& a, Ball& b) {
	int radius = a.getRadius();

	int aX = a.getPosition().x + radius;
	int aY = a.getPosition().y + radius;

	int bX = b.getPosition().x + radius;
	int bY = b.getPosition().y + radius;

	if (aX < bX - radius && aY < bY - radius) return Side::CORNER;
	if (aX < bX - radius && aY > bY + radius) return Side::CORNER;
	if (aX > bX + radius && aY > bY + radius) return Side::CORNER;
	if (aX > bX + radius && aY < bY - radius) return Side::CORNER;

	if (aX > bX + radius) return Side::HORIZONTAL;
	if (aX < bX - radius) return Side::HORIZONTAL;

	return Side::HORIZONTAL;

}

void Physics::ballBallCollision(list<Ball>& balls) {
	auto li = balls.begin();
	for (li; li != balls.end(); li++)
	{
		for (auto e = li; e != balls.end(); e++) {
			if (li == e) continue;
			if (intersects((*li).getBall(), (*e).getBall())) {
				if (side(*li, *e) == Side::CORNER)
				{
					auto    s       = (*e).getPosition() - (*li).getPosition();
					int     bias    = abs(ceil(sqrt(2 * (*e).getRadius() / 2)));

					if (s.x >= 0 && s.y >= 0) (*li).setPosition((*e).getPosition().x - bias, (*e).getPosition().y - bias);
					if (s.x >= 0 && s.y <= 0) (*li).setPosition((*e).getPosition().x - bias, (*e).getPosition().y + bias);
					if (s.x <= 0 && s.y >= 0) (*li).setPosition((*e).getPosition().x + bias, (*e).getPosition().y - bias);
					if (s.x <= 0 && s.y >= 0) (*li).setPosition((*e).getPosition().x + bias, (*e).getPosition().y + bias);

					(*e)     .reverseSpeedY();
					(*li)    .reverseSpeedY();
					(*e)     .reverseSpeedX();
					(*li)    .reverseSpeedX();;
				}
				if (side(*li, *e) == Side::VERTICAL)
				{
					if      ((*li).getPosition().y < (*e).getPosition().y)    (*li)    .setPosition((*li).getPosition().x    , (*e).getPosition().y - (*li).getRadius() * 2);
					else                                                      (*e)     .setPosition((*e).getPosition().x     , (*li).getPosition().y - (*e).getRadius() * 2);

					(*e)     .reverseSpeedY();
					(*li)    .reverseSpeedY();
				}
				if (side(*li, *e) == Side::HORIZONTAL)
				{
					if ((*li).getPosition().x < (*e).getPosition().x)    (*li)    .setPosition((*e).getPosition().x - (*li).getRadius() * 2    , (*li).getPosition().y);
					else                                                 (*e)     .setPosition((*li).getPosition().x - (*e).getRadius() * 2    , (*e).getPosition().y);

					(*e)     .reverseSpeedX();
					(*li)    .reverseSpeedX();
				}
			}
		}
	}
}
	

void Physics::checkCollisions(list<Ball>& balls, vector<vector<Block>>& blocks, Platform& platform, sf::RenderWindow& window, float elapsed, Counter& counter) {
	for (auto& ball : balls) {
		platformBallCollision    (ball, platform, counter, window, elapsed);
		ballBlocksCollision      (ball, blocks, elapsed, counter, platform);
		ballScreenCollision      (ball, window, counter, platform);
	}
	ballBallCollision(balls);
}
