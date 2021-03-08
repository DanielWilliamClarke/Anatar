#include "single_beam_weapon_component.h"

#include "util/math_utils.h"

#include "bullet/i_bullet_system.h"
#include "bullet/i_bullet_system.h"
#include "bullet/bullet.h"
#include "bullet/types/beam.h"

SingleBeamWeaponComponent::SingleBeamWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float duration, float coolDown)
	: bulletSystem(bulletSystem), factory(factory), duration(duration), coolDown(coolDown), accumulator(0.0f), beam(nullptr)
{
}

void SingleBeamWeaponComponent::Fire(sf::Vector2f position, std::shared_ptr<BulletConfig> config)
{
	if (!beam)
	{
		auto theta = AngleConversion::ToRadians(0.0f);
		sf::Vector2f velocity(std::cos(theta) * (float)config->affinity ,std::sin(theta));
		auto traj = BulletTrajectory(position, velocity, config->speed);
		beam = std::dynamic_pointer_cast<Beam>(
			this->bulletSystem->FireBullet(factory, traj, config));
	}

	this->accumulator += this->clock.restart().asSeconds();
	if (!beam->isSpent() && this->accumulator < this->duration)
	{
		beam->Reignite();
		return;
	} 

	if (beam->isSpent() && this->accumulator > coolDown) {
		// once beam is depleted, wait for a while before creating a new beam
		beam = nullptr;
		this->accumulator = 0;
	}
}