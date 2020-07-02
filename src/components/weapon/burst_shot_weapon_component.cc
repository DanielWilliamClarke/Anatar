#include "burst_shot_weapon_component.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../bullet/i_bullet_system.h"

BusrtShotWeaponComponent::BusrtShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, float arcAngle, float numBullets)
	: bulletSystem(bulletSystem), arcAngle(arcAngle * (M_PI / 180.0)), numBullets(numBullets), delay(1.0f), accumulator(0.0f)
{}

void BusrtShotWeaponComponent::Fire(sf::Vector2f position)
{
	this->accumulator += this->clockFire.restart().asSeconds();
	if (this->accumulator >= this->delay)
	{
		this->accumulator -= this->delay;

		// burst center point is (360 - theta) / 2
		float thetaStart = ((M_PI * 2) - arcAngle) / 2;
		float thetaEnd = thetaStart + arcAngle;

		for (float theta = thetaStart; theta < thetaEnd; theta += arcAngle / numBullets)
		{
			sf::Vector2f arcVelocity(180.0f* std::cos(theta), 180.0f * std::sin(theta));
			this->bulletSystem->FireBullet(position, arcVelocity, sf::Color::Red, 3.0f);
		}
	}
}