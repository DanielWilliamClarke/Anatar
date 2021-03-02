#include "bullet_system.h"
#include "types/projectile.h"

#include "i_bullet_factory.h"
#include "entity/entity.h"
#include "components/weapon/i_weapon_component.h"
#include "components/hitbox/i_hitbox_component.h"

#include "util/container_utils.h"

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
	auto chunks = ArrayUtils::Chunk<
		std::vector<std::shared_ptr<Bullet>>,
		std::vector<std::vector<std::shared_ptr<Bullet>>>>
		(this->bullets, 10);

	updateThreads.reserve(chunks.size());
	for (auto& chunk : chunks) 
	{
		updateThreads.push_back(
			std::move(
				std::thread(
					[&](std::vector<std::shared_ptr<Bullet>>& bullets) { 
						this->UpdateBullets(chunk, collisionTargets, dt, worldSpeed);
					},	chunk)));
	}
	for (auto& t : updateThreads)
	{
		if (t.joinable()) {
			t.join();
		}
	}
	updateThreads.clear();

	this->bullets.erase(
		std::remove_if(
			this->bullets.begin(), this->bullets.end(),
			[this](std::shared_ptr<Bullet>& b) -> bool {
				return b->isSpent() || !this->bounds.contains(b->GetPosition());
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

void BulletSystem::UpdateBullets(std::vector<std::shared_ptr<Bullet>>& bullets, std::vector<std::shared_ptr<Entity>>& collisionTargets, float& dt, float& worldSpeed)
{
	for (auto& b : bullets)
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
					if (b->GetOwner() && c.target->HasDied())
					{
						b->GetOwner()->RegisterKill(damage);
					}
				}
			}
		}
	}
}