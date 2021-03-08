#ifndef SINGLE_BEAM_WEAPON_COMPONENT_H
#define SINGLE_BEAM_WEAPON_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "components/weapon/i_weapon_component.h"

class IBulletSystem;
class IBulletFactory;
class Beam;

class SingleBeamWeaponComponent : public IWeaponComponent
{
public:
	SingleBeamWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float duration, float coolDown);
	virtual ~SingleBeamWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position, std::shared_ptr<BulletConfig> config) override;

private:
	std::shared_ptr<IBulletSystem> bulletSystem;
	std::shared_ptr<IBulletFactory> factory;
	std::shared_ptr<Beam> beam;

	sf::Clock clock;
	float accumulator;
	float duration;
	float coolDown;
};

#endif //SINGLE_BEAM_WEAPON_COMPONENT_H