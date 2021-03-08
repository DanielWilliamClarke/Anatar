#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet/bullet.h"
#include "quad_tree/quad_tree.h"

class Entity;

class Projectile : public Bullet
{
public:
	Projectile(BulletTrajectory& trajectory, BulletConfig config);
	virtual ~Projectile() = default;

	virtual void Update(float dt, float worldSpeed) override;
	virtual void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp) override;
	virtual std::vector<EntityCollision> DetectCollisions(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree) override;

protected:

	std::shared_ptr<Entity> FindClosest(std::vector<std::shared_ptr<Entity>> targets) const;

protected:

	std::shared_ptr<sf::Shape> round; // Holds the bullet shape / position etc
};

#endif // PROJECTILE_H
