#ifndef I_BULLET_FACTORY_H
#define I_BULLET_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
struct BulletTrajectory;

class IBulletFactory
{
public:
	IBulletFactory() = default;
	virtual ~IBulletFactory() = default;

	virtual std::shared_ptr<Bullet> Construct(BulletTrajectory& trajectory, std::shared_ptr<BulletConfig> config) const = 0;
};

#endif // I_BULLET_SYSTEM_H
