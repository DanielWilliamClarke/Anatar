#include "single_shot_weapon_component.h"
#include "../../bullet/i_bullet_system.h"

SingleShotWeaponComponent::SingleShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, float delay)
	: bulletSystem(bulletSystem), delay(delay), accumulator(0.0f)
{
}

void SingleShotWeaponComponent::Fire(sf::Vector2f position)
{
	this->accumulator += this->clockFire.restart().asSeconds();
	if (this->accumulator >= this->delay)
	{
		this->accumulator -= this->delay;
		this->bulletSystem->FireBullet(position, { -180.0f, 0 }, sf::Color::Red, 3.0f);
	}
}