#ifndef HOMING_PROJECTILE_H
#define HOMING_PROJECTILE_H
#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.h"

class HomingProjectile : public Projectile
{
public:
	HomingProjectile(BulletTrajectory& trajectory, BulletConfig config);
	virtual ~HomingProjectile() = default;
	virtual std::vector<EntityCollision> DetectCollisions(std::vector<std::shared_ptr<Entity>> targets) override;
private:
	std::shared_ptr<sf::Shape> round; // Holds the bullet shape / position etc
	float mass;
	float G;
};

#endif // HOMING_PROJECTILE_H