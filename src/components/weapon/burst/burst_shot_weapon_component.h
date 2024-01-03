#ifndef BURST_SHOT_WEAPON_COMPONENT_H
#define BURST_SHOT_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>

#include <memory>

#include "components/weapon/i_weapon_component.h"

class IBulletSystem;
class IBulletFactory;

class BurstShotWeaponComponent
    : public IWeaponComponent,
      public WeaponBulletSystemAccess,
      public WeaponBulletFactoryAccess
{
public:
	BurstShotWeaponComponent(
        float numBullets,
        float delay,
        float arcAngle,
        float offsetAngle = 0.0f
    );
	~BurstShotWeaponComponent() override = default;

    [[nodiscard]] WeaponState getWeaponState() const override;
	void Fire(sf::Vector2f position, BulletConfig& config) override;

private:
	float arcAngle;
	float offsetAngle;
	float numBullets;

	sf::Clock clockFire;
	float accumulator;
	float delay;
};

#endif