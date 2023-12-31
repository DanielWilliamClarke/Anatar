#ifndef DEBRIS_FACTORY_H
#define DEBRIS_FACTORY_H


#include <SFML/Graphics.hpp>

#include "bullet/i_bullet_factory.h"
#include "debris.h"
#include "bullet/bullet.h"

class DebrisFactory : public IBulletFactory
{
public:
	DebrisFactory() = default;
	~DebrisFactory() override = default;

	std::shared_ptr<Bullet> Construct(BulletTrajectory& trajectory, BulletConfig& config) const override {
		return std::make_shared<Debris>(trajectory, config);
	};
};

#endif //DEBRIS_FACTORY_H