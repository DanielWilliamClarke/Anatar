#include "bullet_system.h"
#include "types/projectile.h"

#include "i_bullet_factory.h"
#include "entity/entity.h"
#include "components/weapon/i_weapon_component.h"
#include "components/hitbox/i_hitbox_component.h"

#include "util/container_utils.h"
#include "util/i_threaded_workload.h"

BulletSystem::BulletSystem(std::shared_ptr<IThreadedWorkload> threadableWorkload, sf::FloatRect bounds, int affinity)
	: threadableWorkload(threadableWorkload), bounds(bounds), affinity(affinity)
{}

std::shared_ptr<Bullet> BulletSystem::FireBullet(std::shared_ptr<IBulletFactory> factory, sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
{
	auto alignedVelocity = sf::Vector2f(velocity.x * (float)affinity, velocity.y);
	auto bullet = factory->Construct(position, alignedVelocity, config);
	this->AddBullet(bullet);
	return bullet;
}

void BulletSystem::Update(float dt, float worldSpeed, std::vector<std::shared_ptr<Entity>>& collisionTargets)
{
	this->MultiThreadedUpdate(dt, worldSpeed, collisionTargets);
	this->EraseBullets();
}

void BulletSystem::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	for (auto& b : this->bullets)
	{
		b->Draw(renderer, interp);
	}
}

void BulletSystem::AddBullet(std::shared_ptr<Bullet> bullet)
{
	std::lock_guard<std::mutex> lock(this->mutex);
	this->bullets.push_back(bullet);
}

void BulletSystem::MultiThreadedUpdate(float dt, float worldSpeed, std::vector<std::shared_ptr<Entity>>& collisionTargets)
{
	auto chunks = ArrayUtils::Chunk<
		std::vector<std::shared_ptr<Bullet>>,
		std::vector<std::vector<std::shared_ptr<Bullet>>>>
		(this->bullets, 10);

	this->threadableWorkload->Reserve(chunks.size());
	for (auto& chunk : chunks)
	{
		this->threadableWorkload
			->AddThread(std::thread(
				[&](std::vector<std::shared_ptr<Bullet>>& bullets) {
					this->UpdateBullets(chunk, collisionTargets, dt, worldSpeed);
				}, chunk));
	}
	this->threadableWorkload->Join();
}

void BulletSystem::UpdateBullets(std::vector<std::shared_ptr<Bullet>>& bullets, std::vector<std::shared_ptr<Entity>>& collisionTargets, float& dt, float& worldSpeed) const
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

void BulletSystem::EraseBullets()
{
	std::lock_guard<std::mutex> lock(this->mutex);
	this->bullets.erase(
		std::remove_if(
			this->bullets.begin(), this->bullets.end(),
			[this](std::shared_ptr<Bullet>& b) -> bool {
				return b->isSpent() || !this->bounds.contains(b->GetPosition());
			}),
		this->bullets.end());
}