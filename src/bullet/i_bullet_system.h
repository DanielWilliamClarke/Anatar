#ifndef I_BULLET_SYSTEM_H
#define I_BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class IBulletFactory;

class IBulletSystem
{
public:
	IBulletSystem() = default;
	virtual ~IBulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, std::shared_ptr<BulletConfig> config) = 0;
};

#endif // I_BULLET_SYSTEM_H
