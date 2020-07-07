#include "player_weapon_component.h"

PlayerWeaponComponent::PlayerWeaponComponent(std::shared_ptr<IWeaponComponent> weaponComponent)
	: weaponComponent(weaponComponent), gunTemp(0.0f), gunReload(0.3f), gunReloadTime(0.0f)
{}

void PlayerWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	auto elapsedTime = this->clockFire.restart().asSeconds();

	bool canFire = false;
	gunReloadTime -= elapsedTime;
	if (gunReloadTime <= 0.0f)
	{
		canFire = true;
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