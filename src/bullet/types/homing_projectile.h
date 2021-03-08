#ifndef HOMING_PROJECTILE_H
#define HOMING_PROJECTILE_H
#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.h"

class HomingProjectile : public Projectile
{
public:
	HomingProjectile(BulletTrajectory& trajectory, BulletConfig& config);
	virtual ~HomingProjectile() = default;
	virtual std::vector<EntityCollision> DetectCollisions(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree) override;
};

#endif // HOMING_PROJECTILE_H