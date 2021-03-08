#ifndef PLAYER_WEAPON_COMPONENT_H
#define PLAYER_WEAPON_COMPONENT_H
#pragma once

#include <memory>

#include "components/weapon/i_weapon_component.h"

class PlayerWeaponComponent : public IWeaponComponent
{
public:
	PlayerWeaponComponent(std::shared_ptr<IWeaponComponent> weaponComponent);
	virtual ~PlayerWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position, std::shared_ptr<BulletConfig> config) override;

private:

	std::shared_ptr<IWeaponComponent> weaponComponent;

	sf::Clock clockFire;
	float gunTemp;
	float gunReload;
	float gunReloadTime;
};

#endif //PLAYER_WEAPON_COMPONENT_H