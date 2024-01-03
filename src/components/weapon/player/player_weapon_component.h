#ifndef PLAYER_WEAPON_COMPONENT_H
#define PLAYER_WEAPON_COMPONENT_H

#include <memory>

#include "components/weapon/i_weapon_component.h"
#include "components/weapon/accessors/weapon_accessors.h"

class PlayerWeaponComponent
    : public IWeaponComponent
{
public:
	explicit PlayerWeaponComponent(std::shared_ptr<IWeaponComponent> weaponComponent);
	~PlayerWeaponComponent() override = default;

	void Fire(sf::Vector2f position, BulletConfig& config) override;

    [[ nodiscard ]] WeaponSlot getSlot() const override;
    [[nodiscard]] WeaponState getWeaponState() const override;

private:
	std::shared_ptr<IWeaponComponent> weaponComponent;

	sf::Clock clockFire;
	float gunTemp;
	float gunReload;
	float gunReloadTime;
    bool canFire;
};

#endif