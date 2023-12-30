#include "burst_shot_weapon_component.h"

#include "util/math_utils.h"

#include "bullet/i_bullet_system.h"
#include "bullet/i_bullet_factory.h"
#include "bullet/bullet.h"

BurstShotWeaponComponent::BurstShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float numBullets, float delay, float arcAngle, float offsetAngle)
	: bulletSystem(bulletSystem),
	factory(factory),
	arcAngle(numBullets > 1 ? AngleConversion::ToRadians(arcAngle) : 0.0f),
	offsetAngle(AngleConversion::ToRadians(offsetAngle)),
	delay(delay),
	numBullets(numBullets),
	accumulator(0.0f)
{}

void BurstShotWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	this->accumulator += this->clockFire.restart().asSeconds();
	if (this->accumulator >= this->delay)
	{
		this->accumulator = 0;

		auto angleBetween = 0.0f;
		if (numBullets > 1) 
		{
			angleBetween = arcAngle / (numBullets - 1);
		}
			
		// burst center point is (360 - theta) / 2
		float theta = (((float)std::numbers::pi * 2.0f) - arcAngle) / 2.0f;
		for (auto i = 0; i < numBullets; i++) 
		{
			sf::Vector2f arcVelocity(std::cos(theta) * (float)config.affinity, std::sin(theta));
			auto traj = BulletTrajectory(position, -arcVelocity, config.speed);
			this->bulletSystem->FireBullet(factory, traj, config);
			theta += angleBetween;
		}
	}
}