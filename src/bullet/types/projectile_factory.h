#ifndef PROJECTILE_FACTORY_H
#define PROJECTILE_FACTORY_H


#include <SFML/Graphics.hpp>

#include "bullet/i_bullet_factory.h"
#include "projectile.h"
#include "bullet/bullet.h"

class ProjectileFactory : public IBulletFactory
{
public:
	ProjectileFactory() = default;
	~ProjectileFactory() override = default;

	std::shared_ptr<Bullet> Construct(BulletTrajectory& trajectory, BulletConfig& config) const override {
		return std::make_shared<Projectile>(trajectory, config);
	};
};

#endif