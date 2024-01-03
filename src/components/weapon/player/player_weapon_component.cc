#include "player_weapon_component.h"

#include "ui/i_player_hud.h"

PlayerWeaponComponent::PlayerWeaponComponent(std::shared_ptr<IWeaponComponent> weaponComponent)
	: weaponComponent(weaponComponent), gunTemp(0.0f), gunReload(0.2f), gunReloadTime(0.0f)
{}

WeaponSlot PlayerWeaponComponent::getSlot() const
{
    return this->weaponComponent->getSlot();
}

void PlayerWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	auto elapsedTime = this->clockFire.restart().asSeconds();

	this->canFire = false;
	gunReloadTime -= elapsedTime;
	if (gunReloadTime <= 0.0f)
	{
		this->canFire = true;
	}

	gunTemp -= elapsedTime * 10.0f;
	if (gunTemp < 0)
	{
		gunTemp = 0;
	}

	if (canFire && gunTemp < 80.0f)
	{
		gunReloadTime = gunReload;
		gunTemp += 4.0f;
		if (gunTemp > 100.0f)
		{
			gunTemp = 100.0f;
		}

		weaponComponent->Fire(position, config);
	}
}

WeaponState PlayerWeaponComponent::getWeaponState() const
{
    return {
        this->weaponComponent->getWeaponState().type,
        100.0f,
        this->gunTemp,
        this->canFire,
    };
}