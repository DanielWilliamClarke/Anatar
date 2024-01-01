#include "radial_beam_weapon_component.h"

#include "util/math_utils.h"

#include "bullet/i_bullet_system.h"
#include "bullet/i_bullet_system.h"
#include "bullet/bullet.h"
#include "bullet/types/beam.h"

RadialBeamWeaponComponent::RadialBeamWeaponComponent(
    std::shared_ptr<IBulletSystem> bulletSystem,
    std::shared_ptr<IBulletFactory> factory,
    WeaponSlot slot,
    float duration,
    float coolDown,
    float arcAngle,
    float numBeams
)
    : IWeaponComponent(slot),
      bulletSystem(bulletSystem),
      factory(factory),
      arcAngle(numBeams > 1 ? AngleConversion::ToRadians(arcAngle) : 0.0f),
      duration(duration),
      coolDown(coolDown),
      numBeams(numBeams),
      accumulator(0.0f)
{}

void RadialBeamWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	if (beams.empty())
	{
		auto angleBetween = 0.0f;
		if (numBeams > 1)
		{
			angleBetween = arcAngle / (numBeams - 1);
		}

		// burst center point is (360 - theta) / 2
		float theta = (((float)std::numbers::pi * 2.0f) - arcAngle) / 2.0f;
		for (auto i = 0; i < numBeams; i++)
		{
			sf::Vector2f arcVelocity(std::cos(theta) * (float)config.affinity, std::sin(theta));
			auto traj = BulletTrajectory(position, -arcVelocity, config.speed);

			auto beam = std::dynamic_pointer_cast<Beam>(
				this->bulletSystem->FireBullet(factory, traj, config));

			beams.push_back(beam);
			theta += angleBetween;
		}
	}

	// Reigite all beams if still within duration
	this->accumulator += this->clock.restart().asSeconds();
	if (this->accumulator < this->duration)
	{
		for (auto beam : beams)
		{
			if (!beam->isSpent())
			{
				beam->Reignite();
			}
		}
		return;
	}

	// Clear any spent beams
	this->beams.erase(
		std::remove_if(
			this->beams.begin(), this->beams.end(),
			[=](std::shared_ptr<Beam>& b) -> bool {
				return b->isSpent();
			}),
		this->beams.end());

	if (!beams.size() && this->accumulator > this->duration + config.lifeTime + this->coolDown)
	{
		this->accumulator = 0;
	}
}

void RadialBeamWeaponComponent::Cease() {
	std::for_each(beams.begin(), beams.end(), [=](std::shared_ptr<Beam>& b) { b->Cease(); });
}