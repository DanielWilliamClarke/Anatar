#ifndef SINGLE_SHOT_WEAPON_COMPONENT_FACTORY_H
#define SINGLE_SHOT_WEAPON_COMPONENT_FACTORY_H


#include "components/weapon/i_weapon_component_factory.h"
#include "bullet/i_bullet_factory.h"

#include "single_shot_weapon_component.h"

class SingleShotWeaponComponentFactory: public IWeaponComponentFactory
{
public:
	SingleShotWeaponComponentFactory(std::shared_ptr<IBulletFactory> factory)
		: factory(factory)
	{}

	virtual ~SingleShotWeaponComponentFactory() = default;

	virtual std::shared_ptr<IWeaponComponent> Construct(std::shared_ptr<IBulletSystem> bulletSystem, float delay) const override {
		return std::make_shared<SingleShotWeaponComponent>(bulletSystem, factory, delay);
	};

private:
	std::shared_ptr<IBulletFactory> factory;
};

#endif //SINGLE_SHOT_WEAPON_COMPONENT_FACTORY_H