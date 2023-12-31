#ifndef COLLISION_H
#define COLLISION_H

#include <memory>

class Bullet;

template<typename P>
struct Point;

struct CollisionMediators
{
	std::function<bool(float, sf::Vector2f)> resolver;
	std::function<std::shared_ptr<sf::Vector2f>(sf::Vector2f, sf::Vector2f, bool ray)> pointTest;
	std::function<bool(sf::FloatRect&)> zoneTest;

	CollisionMediators SetCollisionResolver(std::function<bool(float, sf::Vector2f)> r) {
		this->resolver = r;
		return *this;
	}

	CollisionMediators SetPointTest(std::function<std::shared_ptr<sf::Vector2f>(sf::Vector2f, sf::Vector2f, bool ray)> pt) {
		this->pointTest = pt;
		return *this;
	}

	CollisionMediators SetZoneTest(std::function<bool(sf::FloatRect&)> zt) {
		this->zoneTest = zt;
		return *this;
	}
};

struct Collision {
	std::shared_ptr<Bullet> bullet;
	std::shared_ptr<Point<CollisionMediators>> target;
	sf::Vector2f collisionPosition;

	Collision(
		std::shared_ptr<Bullet> bullet,
		std::shared_ptr<Point<CollisionMediators>> target,
		sf::Vector2f collisionPosition = sf::Vector2f())
		: bullet(bullet), target(target), collisionPosition(collisionPosition)
	{}
};

#endif // BULLET_H
