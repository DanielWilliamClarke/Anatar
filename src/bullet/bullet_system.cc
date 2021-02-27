#include "bullet_system.h"
#include "projectile.h"

#include "i_bullet_factory.h"
#include "../entity/entity.h"
#include "../components/weapon/i_weapon_component.h"
#include "../components/hitbox/i_hitbox_component.h"

BulletSystem::BulletSystem(sf::FloatRect bounds, int affinity, std::shared_ptr<IWeaponComponent> debrisGenerator, std::shared_ptr<BulletSystemDebrisConfig> debrisConfigs)
	: bounds(bounds), affinity(affinity), debrisGenerator(debrisGenerator), debrisConfigs(debrisConfigs)
{}

std::shared_ptr<Bullet> BulletSystem::FireBullet(std::shared_ptr<IBulletFactory> factory, sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
{
	auto alignedVelocity = sf::Vector2f(velocity.x * (float)affinity, velocity.y);
	auto bullet = factory->Construct(position, alignedVelocity, config);
	this->bullets.push_back(bullet);
	return bullet;
}

void BulletSystem::Update(float dt, float worldSpeed, std::list<std::shared_ptr<Entity>>& collisionTargets)
{
	// Update and perform collision detection
	for (auto&& b : this->bullets)
	{
		b->CollisionDetected(nullptr);

		// Intersect targets with bullet
		std::list<IntersectedTarget> targets;
		std::transform(collisionTargets.begin(), collisionTargets.end(), std::back_inserter(targets),
			[&b](std::shared_ptr<Entity> entity) -> IntersectedTarget {
				return std::make_pair(
					entity,
					entity->DetectCollisionWithRay(b->GetPosition(), b->GetVelocity())
				);
			});

		// Cull targets that do not have intersection
		std::list<IntersectedTarget> culledTargets;
		std::copy_if(targets.begin(), targets.end(), std::back_inserter(culledTargets),
			[=](IntersectedTarget intersectedTarget) -> bool {
				return intersectedTarget.second->intersects;
			});

		// sort elements closest to furthest
		culledTargets.sort(
			[&b](IntersectedTarget targetA, IntersectedTarget targetB) -> bool {
				auto distanceA = targetA.first->DistanceTo(b->GetPosition());
				auto distanceB = targetB.first->DistanceTo(b->GetPosition());
				return distanceA < distanceB;
			});

		for (auto& t : culledTargets)
		{
			if (t.first->DetectCollision(b->GetRound()->getGlobalBounds()))
			{
				auto damage = b->GetDamage();

				// update target
				if (damage.first > 0.0f)
				{
					t.first->TakeDamage(damage.first);
					if (t.first->HasDied() && b->GetOwner())
					{
						b->GetOwner()->RegisterKill(damage.first);
					}

					// Effects
					if (debrisGenerator)
					{
						auto config = *this->debrisConfigs->onCollision;
						if (t.first->HasDied())
						{
							config = *this->debrisConfigs->onDeath;
						}
						debrisGenerator->Fire(t.second->point, config);
					}
				}

				// spend round - we can just go to the next bullet if we dont need to penetrate the enemy
				b->CollisionDetected(&t.second->point);
				if (!damage.second)
				{
					break;
				}
			}
		}

		b->Update(dt, worldSpeed);
	}

	// Remove bullets 
	this->bullets.remove_if([=](std::shared_ptr<Bullet>& b) -> bool {
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
