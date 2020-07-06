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
				auto damage = b.GetDamage();
				c->TakeDamage(damage.first);
				// spend round 
				if (!damage.second)
				{
					b.CollisionDetected();
				}
			}
		}
	}

	// Remove bullets 
	this->bullets.remove_if([=](Bullet b) -> bool {
		auto position = b.GetPosition();
		return position.x <= bounds.left || position.x >= bounds.width ||
			position.y <= bounds.top || position.y >= bounds.height ||
			b.isSpent();
	});
}

void BulletSystem::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	for (auto& b : this->bullets)
	{
		b.Draw(renderer, interp);
	}
}
