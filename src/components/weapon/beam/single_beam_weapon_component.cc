#include "single_beam_weapon_component.h"

#include "../../../bullet/i_bullet_system.h"
#include "../../../bullet/i_bullet_system.h"
#include "../../../bullet/bullet.h"
#include "../../../bullet/beam.h"

SingleBeamWeaponComponent::SingleBeamWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float duration, float coolDown)
	: bulletSystem(bulletSystem), factory(factory), duration(duration), coolDown(coolDown), accumulator(0.0f), beam(nullptr)
{
}

void SingleBeamWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	if (!beam)
	{
		beam = std::dynamic_pointer_cast<Beam>(
			this->bulletSystem->FireBullet(factory, position, { config.speed, 0 }, config));
	}

	this->accumulator += this->clock.restart().asSeconds();
	if (this->accumulator < this->duration)
	{
		beam->Reignite();
	} 
	else
	{
		auto delay = beam->isSpent() ? this->coolDown : this->duration + this->coolDown;
		if (this->accumulator >= delay)
		{
			// once beam is depleted, wait for a while before creating a new beam
			beam = nullptr;
			this->accumulator = 0;
		}
	}
}