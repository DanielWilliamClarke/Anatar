#ifndef SINGLE_SHOT_WEAPON_COMPONENT_FACTORY_H
#define SINGLE_SHOT_WEAPON_COMPONENT_FACTORY_H
#pragma once

#include "../i_weapon_component_factory.h"

#include "single_shot_weapon_component.h"

class SingleShotWeaponComponentFactory: public IWeaponComponentFactory
{
public:
	SingleShotWeaponComponentFactory() = default;

	virtual ~SingleShotWeaponComponentFactory() = default;

	virtual std::shared_ptr<IWeaponComponent> Construct(std::shared_ptr<IBulletSystem> bulletSystem, float delay) const override {
		return std::make_shared<SingleShotWeaponComponent>(bulletSystem, delay);
	};
};

#endif //SINGLE_SHOT_WEAPON_COMPONENT_FACTORY_H