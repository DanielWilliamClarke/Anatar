#ifndef PLAYER_WEAPON_COMPONENT_H
#define PLAYER_WEAPON_COMPONENT_H

#include <memory>

#include "components/weapon/i_weapon_component.h"

class PlayerWeaponComponent : public IWeaponComponent
{
public:
	explicit PlayerWeaponComponent(std::shared_ptr<IWeaponComponent> weaponComponent);
	~PlayerWeaponComponent() override = default;

	void Fire(sf::Vector2f position, BulletConfig& config) override;

private:
	std::shared_ptr<IWeaponComponent> weaponComponent;

	sf::Clock clockFire;
	float gunTemp;
	float gunReload;
	float gunReloadTime;
};

#endif //PLAYER_WEAPON_COMPONENT_H