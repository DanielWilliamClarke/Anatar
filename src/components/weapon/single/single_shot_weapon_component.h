#ifndef SINGLE_SHOT_WEAPON_COMPONENT_H
#define SINGLE_SHOT_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "components/weapon/i_weapon_component.h"

class IBulletSystem;
class IBulletFactory;

class SingleShotWeaponComponent: public IWeaponComponent
{
public:
	SingleShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float delay);
	~SingleShotWeaponComponent() override = default;

	void Fire(sf::Vector2f position, BulletConfig& config) override;

private:
	std::shared_ptr<IBulletSystem> bulletSystem;
	std::shared_ptr<IBulletFactory> factory;
	sf::Clock clockFire;
	float accumulator;
	float delay;
};

#endif //SINGLE_SHOT_WEAPON_COMPONENT_H