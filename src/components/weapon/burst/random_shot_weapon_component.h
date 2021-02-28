#ifndef RANDOM_SHOT_WEAPON_COMPONENT_H
#define RANDOM_SHOT_WEAPON_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "components/weapon/i_weapon_component.h"
#include "util/i_random_number_source.h"

class IBulletSystem;
class IBulletFactory;

class RandomShotWeaponComponent : public IWeaponComponent
{
public:
	RandomShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, std::shared_ptr<IRandomNumberSource<int>> randSource, float numBullets);
	virtual ~RandomShotWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position, BulletConfig& config) override;

private:
	std::shared_ptr<IBulletSystem> bulletSystem;
	std::shared_ptr<IBulletFactory> factory;
	std::shared_ptr<IRandomNumberSource<int>> randSource;
	float numBullets;
};

#endif //RANDOM_SHOT_WEAPON_COMPONENT_H