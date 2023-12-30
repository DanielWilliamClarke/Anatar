#ifndef BURST_SHOT_WEAPON_COMPONENT_FACTORY_H
#define BURST_SHOT_WEAPON_COMPONENT_FACTORY_H


#include "components/weapon/i_weapon_component_factory.h"
#include "bullet/i_bullet_factory.h"

#include "burst_shot_weapon_component.h"

class BurstShotWeaponComponentFactory: public IWeaponComponentFactory
{
public:
	BurstShotWeaponComponentFactory(std::shared_ptr<IBulletFactory> factory, float numBullets, float arcAngle, float offsetAngle = 0.0f)
		: factory(factory),
		numBullets(numBullets),
		arcAngle(arcAngle),
		offsetAngle(offsetAngle)
	{}

	virtual ~BurstShotWeaponComponentFactory() = default;

	virtual std::shared_ptr<IWeaponComponent> Construct(std::shared_ptr<IBulletSystem> bulletSystem, float delay) const override {
		return std::make_shared<BurstShotWeaponComponent>(bulletSystem, factory, numBullets, delay, arcAngle, offsetAngle);
	};

private:
	std::shared_ptr<IBulletFactory> factory;
	float numBullets;
	float arcAngle;
	float offsetAngle;
};

#endif //BURST_SHOT_WEAPON_COMPONENT_FACTORY_H