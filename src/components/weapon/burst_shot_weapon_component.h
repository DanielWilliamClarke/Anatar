#ifndef BURST_SHOT_WEAPON_COMPONENT_H
#define BURST_SHOT_WEAPON_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "i_weapon_component.h"

class IBulletSystem;

class BurstShotWeaponComponent : public IWeaponComponent
{
public:
	BurstShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, float delay, float arcAngle, float numBullets);
	virtual ~BurstShotWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position) override;

private:
	std::shared_ptr<IBulletSystem> bulletSystem;
	float arcAngle;
	float numBullets;

	sf::Clock clockFire;
	float accumulator;
	float delay;
};

#endif //BURST_SHOT_WEAPON_COMPONENT_H