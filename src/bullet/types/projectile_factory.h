#ifndef PROJECTILE_FACTORY_H
#define PROJECTILE_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet/i_bullet_factory.h"
#include "projectile.h"
#include "bullet/bullet.h"

class ProjectileFactory : public IBulletFactory
{
public:
	ProjectileFactory() {}
	virtual ~ProjectileFactory() = default;

	virtual std::shared_ptr<Bullet> Construct(BulletTrajectory& trajectory, std::shared_ptr<BulletConfig> config) const override {
		return std::make_shared<Projectile>(trajectory, config);
	};
};

#endif //PROJECTILE_FACTORY_H