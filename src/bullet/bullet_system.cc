#include "bullet_system.h"
#include "types/projectile.h"

#include "i_bullet_factory.h"
#include "entity/entity.h"
#include "components/weapon/i_weapon_component.h"
#include "components/hitbox/i_hitbox_component.h"

#include "quad_tree/quad_tree.h"

#include "util/container_utils.h"
#include "util/i_threaded_workload.h"

#include "entity/entity.h"

BulletSystem::BulletSystem(sf::FloatRect bounds)
	: bounds(bounds)
{}

std::shared_ptr<Bullet> BulletSystem::FireBullet(std::shared_ptr<IBulletFactory> factory, BulletTrajectory& trajectory, std::shared_ptr<BulletConfig> config)
{
	auto bullet = factory->Construct(trajectory, config);
	this->AddBullet(bullet);
	return bullet;
}

void BulletSystem::Update(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree, float dt, float worldSpeed)
{
	for (auto& b : bullets)
	{
		b->Update(dt, worldSpeed);

		auto collisions = b->DetectCollisions(quadTree);
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