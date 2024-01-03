#ifndef SINGLE_SHOT_WEAPON_COMPONENT_H
#define SINGLE_SHOT_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "components/weapon/i_weapon_component.h"
#include "components/weapon/accessors/weapon_accessors.h"

class IBulletSystem;
class IBulletFactory;

class SingleShotWeaponComponent
    : public IWeaponComponent,
      public WeaponBulletSystemAccess,
      public WeaponBulletFactoryAccess
{
public:
	explicit SingleShotWeaponComponent(float delay);
	~SingleShotWeaponComponent() override = default;

    [[nodiscard]] WeaponState getWeaponState() const override;
	void Fire(sf::Vector2f position, BulletConfig& config) override;

private:
	sf::Clock clockFire;
	float accumulator;
	float delay;
};

#endif