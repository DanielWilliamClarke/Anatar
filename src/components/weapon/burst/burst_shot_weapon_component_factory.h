#ifndef BURST_SHOT_WEAPON_COMPONENT_FACTORY_H
#define BURST_SHOT_WEAPON_COMPONENT_FACTORY_H
#pragma once

#include "../i_weapon_component_factory.h"

#include "burst_shot_weapon_component.h"

class BurstShotWeaponComponentFactory: public IWeaponComponentFactory
{
public:
	BurstShotWeaponComponentFactory(float arcAngle, float numBullets) 
		: arcAngle(arcAngle), numBullets(numBullets)
	{}

	virtual ~BurstShotWeaponComponentFactory() = default;

	virtual std::shared_ptr<IWeaponComponent> Construct(std::shared_ptr<IBulletSystem> bulletSystem, float delay) const override {
		return std::make_shared<BurstShotWeaponComponent>(bulletSystem, delay, arcAngle, numBullets);
	};

private:
	float arcAngle;
	float numBullets;
};

#endif //BURST_SHOT_WEAPON_COMPONENT_FACTORY_H