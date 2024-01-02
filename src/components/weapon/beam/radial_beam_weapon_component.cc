#include "radial_beam_weapon_component.h"

#include <range/v3/algorithm.hpp>

#include "util/math_utils.h"
#include "bullet/i_bullet_system.h"
#include "bullet/bullet.h"
#include "bullet/types/beam.h"
#include "ui/i_player_hud.h"

RadialBeamWeaponComponent::RadialBeamWeaponComponent(
    std::shared_ptr<IBulletSystem> bulletSystem,
    std::shared_ptr<IBulletFactory> factory,
    std::shared_ptr<IPlayerHud> hud,
    WeaponSlot slot,
    float duration,
    float coolDown,
    float arcAngle,
    float numBeams
)
    : IWeaponComponent(hud, slot),
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
				this->bulletSystem->FireBullet(factory, traj, config)
            );

			beams.push_back(beam);
			theta += angleBetween;
		}
	}

	// Reigite all beams if still within duration
	this->accumulator += this->clock.restart().asSeconds();
	if (this->accumulator < this->duration)
	{
        ranges::for_each(beams, [=](std::shared_ptr<Beam>& b) {
            if (!b->isSpent())
            {
                b->Reignite();
            }
        });
		return;
	}

	// Clear any spent beams
    std::erase_if(this->beams, [=](std::shared_ptr<Beam>& b) -> bool {
        return b->isSpent();
    });

	if (
        beams.empty() &&
        this->accumulator > this->duration + config.lifeTime + this->coolDown
    )
	{
		this->accumulator = 0;
	}
}

void RadialBeamWeaponComponent::Cease() {
	ranges::for_each(beams, [=](std::shared_ptr<Beam>& b) {
        b->Cease();
    });
}

WeaponState RadialBeamWeaponComponent::getWeaponState() const
{
    return {
        "MultiBeam",
        this->duration + this->coolDown,
        this->accumulator,
        true
    };
}