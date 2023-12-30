#ifndef HOMING_PROJECTILE_FACTORY_H
#define HOMING_PROJECTILE_FACTORY_H


#include <SFML/Graphics.hpp>

#include "bullet/i_bullet_factory.h"
#include "homing_projectile.h"
#include "bullet/bullet.h"

class HomingProjectileFactory : public IBulletFactory
{
public:
	HomingProjectileFactory() {}
	virtual ~HomingProjectileFactory() = default;

	virtual std::shared_ptr<Bullet> Construct(BulletTrajectory& trajectory, BulletConfig& config) const override {
		return std::make_shared<HomingProjectile>(trajectory, config);
	};
};

#endif //HOMING_PROJECTILE_FACTORY_H