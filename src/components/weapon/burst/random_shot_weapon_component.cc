#include "random_shot_weapon_component.h"

#include "util/math_utils.h"

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
		auto theta = AngleConversion::ToRadians(randSource->Generate(0, 360));
		auto speed = config.speed * randSource->Generate(50, 250) / 100;
		sf::Vector2f arcVelocity(speed * std::cos(theta), speed * std::sin(theta));
		this->bulletSystem->FireBullet(factory, position, arcVelocity, config);
	}
}