#include "burst_shot_weapon_component.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../../bullet/i_bullet_system.h"
#include "../../../bullet/i_bullet_factory.h"
#include "../../../bullet/bullet.h"

BurstShotWeaponComponent::BurstShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, float delay, float arcAngle, float numBullets)
	: bulletSystem(bulletSystem), factory(factory), arcAngle(arcAngle * ((float)M_PI / 180.0f)), delay(delay), numBullets(numBullets), accumulator(0.0f)
{}

void BurstShotWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	this->accumulator += this->clockFire.restart().asSeconds();
	if (this->accumulator >= this->delay)
	{
		this->accumulator = 0;

		// burst center point is (360 - theta) / 2
		float thetaStart = (((float)M_PI * 2.0f) - arcAngle) / 2.0f;
		float thetaEnd = thetaStart + arcAngle;

		for (float theta = thetaStart; theta < thetaEnd; theta += arcAngle / numBullets)
		{
			sf::Vector2f arcVelocity(config.speed * std::cos(theta), config.speed * std::sin(theta));
			this->bulletSystem->FireBullet(factory, position, -arcVelocity, config);
		}
	}
}