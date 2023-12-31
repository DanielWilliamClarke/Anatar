#ifndef DEBRIS_H
#define DEBRIS_H

#include <SFML/Graphics.hpp>

#include "projectile.h"

struct Collision;

class Debris : public Projectile
{
public:
	Debris(BulletTrajectory& trajectory, BulletConfig& config) 
		: Projectile(trajectory, config)
	{}

	~Debris() override = default;

	std::vector<std::shared_ptr<Collision>> DetectCollisions(const CollisionQuadTree& quadTree) override { return {}; }
};

#endif // DEBRIS_H