#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "i_bullet_system.h"

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class Entity;
struct EntityCollision;
class IRenderer;
class IThreadedWorkload;

template<typename U, typename C>
class QuadTree;

typedef QuadTree<Entity, EntityCollision> CollisionQuadTree;

class BulletSystem : public IBulletSystem
{
public:

	BulletSystem(sf::FloatRect bounds);
	virtual ~BulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) override;
	void Update(std::shared_ptr<CollisionQuadTree> quadTree, float dt, float worldSpeed);
	void Draw(std::shared_ptr<IRenderer> renderer, float interp);

private:

	void AddBullet(std::shared_ptr<Bullet> bullet);
	void EraseBullets();

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::FloatRect bounds;
};

#endif // BULLET_SYSTEM_H