#ifndef BURST_SHOT_WEAPON_COMPONENT_H
#define BURST_SHOT_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>

#include <memory>

#include "components/weapon/i_weapon_component.h"

class IBulletSystem;
class IBulletFactory;

class BurstShotWeaponComponent : public IWeaponComponent
{
public:
	BurstShotWeaponComponent(
        std::shared_ptr<IBulletSystem> bulletSystem,
        std::shared_ptr<IBulletFactory> factory,
        std::shared_ptr<IPlayerHud> hud,
        WeaponSlot slot,
        float numBullets,
        float delay,
        float arcAngle,
        float offsetAngle = 0.0f
    );
	~BurstShotWeaponComponent() override = default;

    [[nodiscard]] WeaponState getWeaponState() const override;
	void Fire(sf::Vector2f position, BulletConfig& config) override;

private:
	std::shared_ptr<IBulletSystem> bulletSystem;
	std::shared_ptr<IBulletFactory> factory;

	float arcAngle;
	float offsetAngle;
	float numBullets;

	sf::Clock clockFire;
	float accumulator;
	float delay;
};

#endif