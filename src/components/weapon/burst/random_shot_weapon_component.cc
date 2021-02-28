#include "random_shot_weapon_component.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "bullet/i_bullet_system.h"
#include "bullet/i_bullet_factory.h"
#include "bullet/bullet.h"

RandomShotWeaponComponent::RandomShotWeaponComponent(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IBulletFactory> factory, std::shared_ptr<IRandomNumberSource<int>> randSource, float numBullets)
	: bulletSystem(bulletSystem), factory(factory), randSource(randSource), numBullets(numBullets)
{}

void RandomShotWeaponComponent::Fire(sf::Vector2f position, BulletConfig& config)
{
	for (float i = 0; i < numBullets; i++)
	{
		auto theta = randSource->Generate(0, 360) * ((float)M_PI / 180.0f);
		auto speed = config.speed * randSource->Generate(50, 250) / 100;
		sf::Vector2f arcVelocity(speed * std::cos(theta), speed * std::sin(theta));
		this->bulletSystem->FireBullet(factory, position, arcVelocity, config);
	}
}