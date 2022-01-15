#ifndef I_BULLET_SYSTEM_H
#define I_BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class IBulletFactory;

struct Collision;
struct CollisionMediators;
template<typename C, typename P>
class QuadTree;

class IRenderer;

class IBulletSystem
{
public:
	IBulletSystem() = default;
	virtual ~IBulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) = 0;

	virtual void Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, float dt, float worldSpeed) {}
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) {}
};

#endif // I_BULLET_SYSTEM_H
