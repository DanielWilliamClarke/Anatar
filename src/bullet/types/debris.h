#ifndef DEBRIS_H
#define DEBRIS_H
#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.h"

struct Collision;
template<typename C>
class QuadTree;

class Debris : public Projectile
{
public:
	Debris(BulletTrajectory& trajectory, BulletConfig& config) 
		: Projectile(trajectory, config)
	{}

	virtual ~Debris() = default;

	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(std::shared_ptr<QuadTree<Collision>> quadTree) override { return {}; }
};

#endif // DEBRIS_H