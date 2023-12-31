#ifndef I_BULLET_SYSTEM_H
#define I_BULLET_SYSTEM_H

#include <SFML/Graphics.hpp>
#include "quad_tree/collision_quad_tree.h"

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class IBulletFactory;

class IRenderer;

class IBulletSystem
{
public:
	IBulletSystem() = default;
	virtual ~IBulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) = 0;

	virtual void Update(const CollisionQuadTree& quadTree, float dt, float worldSpeed) {}
	virtual void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) {}
};

#endif
