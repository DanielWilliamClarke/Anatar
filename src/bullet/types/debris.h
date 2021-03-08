#ifndef DEBRIS_H
#define DEBRIS_H
#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.h"

class Debris : public Projectile
{
public:
	Debris(BulletTrajectory& trajectory, BulletConfig& config) 
		: Projectile(trajectory, config)
	{}

	virtual ~Debris() = default;

	virtual std::vector<EntityCollision> DetectCollisions(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree) override { return {}; }
};

#endif // DEBRIS_H