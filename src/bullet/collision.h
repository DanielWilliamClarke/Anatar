#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include <memory>

class Bullet;
struct Point;

struct Collision {
	std::shared_ptr<Bullet> bullet;
	std::shared_ptr<Point> target;

	Collision(
		std::shared_ptr<Bullet> bullet,
		std::shared_ptr<Point> target)
		: bullet(bullet), target(target)
	{}
};

#endif // BULLET_H
