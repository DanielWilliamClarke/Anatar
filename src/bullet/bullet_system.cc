#include "bullet_system.h"
#include "bullet.h"

#include "../entity/entity.h"

BulletSystem::BulletSystem(sf::FloatRect bounds, int affinity)
	: bounds(bounds), affinity(affinity)
{}

void BulletSystem::FireBullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
{
	auto alignedVelocity = sf::Vector2f(velocity.x * (float)affinity, velocity.y);
	this->bullets.push_back(Bullet(position, alignedVelocity, config));
}

void BulletSystem::Update(float dt, float worldSpeed, std::list<std::shared_ptr<Entity>> collisionTargets)
{
	// Update and perform collision detection
	for (auto& b : this->bullets)
	{
		b.Update(dt, worldSpeed);

		for (auto& c : collisionTargets)
		{
			

			if (c->DetectCollision(b.GetRound()->getGlobalBounds()))
			{
				// update entity

				// spend round 
				b.CollisionDetected();
			}
		}
	}

	// Remove bullets 
	this->bullets.remove_if([=](Bullet b) -> bool {
		auto position = b.GetRound()->getPosition();
		return position.x <= bounds.left ||	position.x >= bounds.width ||
			position.y <= bounds.top ||	position.y >= bounds.height ||
			b.isSpent();
	});
}

void BulletSystem::Draw(sf::RenderTarget& target, float interp)
{
	for (auto& b : this->bullets)
	{
		b.Draw(target, interp);
	}
}
