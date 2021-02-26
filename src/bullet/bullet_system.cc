#include "bullet_system.h"
#include "bullet.h"

#include "../entity/entity.h"

#include "../components/weapon/i_weapon_component.h"

BulletSystem::BulletSystem(sf::FloatRect bounds, int affinity, std::shared_ptr<IWeaponComponent> debrisGenerator, std::shared_ptr<BulletSystemDebrisConfig> debrisConfigs)
	: bounds(bounds), affinity(affinity), debrisGenerator(debrisGenerator), debrisConfigs(debrisConfigs)
{}

void BulletSystem::FireBullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
{
	auto alignedVelocity = sf::Vector2f(velocity.x * (float)affinity, velocity.y);
	this->bullets.push_back(std::make_unique<Bullet>(position, alignedVelocity, config));
}

void BulletSystem::Update(float dt, float worldSpeed, std::list<std::shared_ptr<Entity>>& collisionTargets)
{
	// Update and perform collision detection
	for (auto&& b : this->bullets)
	{
		collisionTargets.sort(
			[&b](std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB) -> bool {
				auto distanceA = entityA->DistanceTo(b->GetPosition());
				auto distanceB = entityB->DistanceTo(b->GetPosition());
				return distanceA < distanceB;
			});

		for (auto& c : collisionTargets)
		{
			if (c->DetectCollision(b->GetRound()->getGlobalBounds()))
			{
				b->CollisionDetected(c->GetPosition());

				// update entity
				auto damage = b->GetDamage();
				c->TakeDamage(damage.first);
				if (c->HasDied())
				{
					if (b->GetOwner())
					{
						b->GetOwner()->RegisterKill(damage.first);
					}
					if (debrisGenerator)
					{
						debrisGenerator->Fire(b->GetPosition(), *this->debrisConfigs->onDeath);
					}
				}

				if (debrisGenerator)
				{
					auto config = *this->debrisConfigs->onCollision;
					if (c->HasDied())
					{
						config = *this->debrisConfigs->onDeath;
					}
					debrisGenerator->Fire(b->GetPosition(), config);
				}


				// spend round - we can just go to the next bullet if we dont need to penetrate the enemy
				if (!damage.second)
				{
					break;
				}
			}
		}

		b->Update(dt, worldSpeed);
	}

	// Remove bullets 
	this->bullets.remove_if([=](std::unique_ptr<Bullet>& b) -> bool {
		auto position = b->GetPosition();
		return position.x <= bounds.left || position.x >= bounds.width ||
			position.y <= bounds.top || position.y >= bounds.height ||
			b->isSpent();
		});
}

void BulletSystem::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	for (auto& b : this->bullets)
	{
		b->Draw(renderer, interp);
	}
}
