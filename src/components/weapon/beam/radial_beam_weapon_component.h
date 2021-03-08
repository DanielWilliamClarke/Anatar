#ifndef RADIAL_BEAM_WEAPON_COMPONENT_H
#define RADIAL_BEAM_WEAPON_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "components/weapon/i_weapon_component.h"

class IBulletSystem;
class IBulletFactory;
class Beam;

class RadialBeamWeaponComponent : public IWeaponComponent
{
public:
	RadialBeamWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float duration, float coolDown, float arcAngle, float numBeams);
	virtual ~RadialBeamWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position, std::shared_ptr<BulletConfig> config) override;

private:
	std::shared_ptr<IBulletSystem> bulletSystem;
	std::shared_ptr<IBulletFactory> factory;
	std::vector<std::shared_ptr<Beam>> beams;

	float arcAngle;
	float numBeams;

	sf::Clock clock;
	float accumulator;
	float duration;
	float coolDown;
};

#endif //RADIAL_BEAM_WEAPON_COMPONENT_H