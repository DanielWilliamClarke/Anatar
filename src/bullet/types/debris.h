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

	virtual std::vector<std::shared_ptr<EntityCollision>> DetectCollisions(std::shared_ptr<CollisionQuadTree> quadTree) override { return {}; }
};

#endif // DEBRIS_H