#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "i_bullet_system.h"
#include "quad_tree/quad_tree.h"


class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class Entity;
struct EntityCollision;
class IGlowShaderRenderer;
class IThreadedWorkload;

class BulletSystem : public IBulletSystem
{
public:

	BulletSystem(sf::FloatRect bounds);
	virtual ~BulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) override;
	void Update(std::shared_ptr<QuadTree<std::shared_ptr<Entity>, std::shared_ptr<EntityCollision>>> quadTree, float dt, float worldSpeed);
	void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp);

private:

	void AddBullet(std::shared_ptr<Bullet> bullet);
	void EraseBullets();

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::FloatRect bounds;
};

#endif // BULLET_SYSTEM_H