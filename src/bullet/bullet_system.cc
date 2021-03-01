#include "bullet_system.h"
#include "types/projectile.h"

#include "i_bullet_factory.h"
#include "entity/entity.h"
#include "components/weapon/i_weapon_component.h"
#include "components/hitbox/i_hitbox_component.h"

BulletSystem::BulletSystem(sf::FloatRect bounds, int affinity)
	: bounds(bounds), affinity(affinity)
{}

std::shared_ptr<Bullet> BulletSystem::FireBullet(std::shared_ptr<IBulletFactory> factory, sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
{
	auto alignedVelocity = sf::Vector2f(velocity.x * (float)affinity, velocity.y);
	auto bullet = factory->Construct(position, alignedVelocity, config);
	this->bullets.push_back(bullet);
	return bullet;
}

void BulletSystem::Update(float dt, float worldSpeed, std::vector<std::shared_ptr<Entity>>& collisionTargets)
{
	// Update and perform collision detection
	for (auto& b : this->bullets)
	{
		b->Update(dt, worldSpeed);

		if (collisionTargets.size())
		{
			auto collisions = b->DetectCollisions(collisionTargets);
			auto damage = b->GetDamage();
			if (damage > 0.0f)
			{
				for (auto& c : collisions)
				{
					// update target
					c.target->TakeDamage(damage, c.point);
					if (c.target->HasDied() && b->GetOwner())
					{
						b->GetOwner()->RegisterKill(damage);
					}
				}
			}
		}
	}

	this->bullets.erase(
		std::remove_if(
			this->bullets.begin(), this->bullets.end(),
			[=](std::shared_ptr<Bullet>& b) -> bool {
				auto position = b->GetPosition();
				return position.x <= bounds.left || position.x >= bounds.width ||
					position.y <= bounds.top || position.y >= bounds.height ||
					b->isSpent();
			}),
		this->bullets.end());
}

void BulletSystem::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	for (auto& b : this->bullets)
	{
		b->Draw(renderer, interp);
	}
}
