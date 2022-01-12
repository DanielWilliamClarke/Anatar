#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include <memory>

class Bullet;
struct Point;

struct Collision {
	std::shared_ptr<Bullet> bullet;
	std::shared_ptr<Point> target;
	sf::Vector2f collisionPosition;

	Collision(
		std::shared_ptr<Bullet> bullet,
		std::shared_ptr<Point> target,
		sf::Vector2f collisionPosition = sf::Vector2f())
		: bullet(bullet), target(target), collisionPosition(collisionPosition)
	{}
};

#endif // BULLET_H
