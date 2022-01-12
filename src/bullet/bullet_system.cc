#include "bullet_system.h"

#include <algorithm>

#include "types/projectile.h"

#include "i_bullet_factory.h"

#include "components/weapon/i_weapon_component.h"
#include "components/hitbox/i_hitbox_component.h"

#include "quad_tree/quad_tree.h"
#include "util/container_utils.h"
#include "util/i_threaded_workload.h"

#include "bullet/collision.h"

BulletSystem::BulletSystem(sf::FloatRect bounds)
	: bounds(bounds)
{}

std::shared_ptr<Bullet> BulletSystem::FireBullet(std::shared_ptr<IBulletFactory> factory, BulletTrajectory& trajectory, BulletConfig& config)
{
	auto bullet = factory->Construct(trajectory, config);
	this->AddBullet(bullet);
	return bullet;
}

void BulletSystem::Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, float dt, float worldSpeed)
{
	this->EraseBullets();

	// Determine collisions to resolve
	std::vector<std::shared_ptr<Collision>> unresolved;
	for (auto& b : this->bullets)
	{
		b->Update(dt, worldSpeed);

		auto collisions = b->DetectCollisions(quadTree);
		if (collisions.size() && b->GetDamage() > 0.0f)
		{
			unresolved.reserve(std::max(unresolved.capacity(), unresolved.size() + collisions.size()));
			unresolved.insert(unresolved.end(), collisions.begin(), collisions.end());
		}
	}

	// Resolve each collision
	std::for_each(unresolved.begin(), unresolved.end(),
		[&](std::shared_ptr<Collision> c) {
			auto damage = c->bullet->GetDamage();
			c->bullet->GetCollisionResolver()(
				c->target->payload->resolver(damage, c->collisionPosition),
				damage);
		});
}

void BulletSystem::Draw(std::shared_ptr<IRenderer> renderer, float interp)
{
	for (auto& b : this->bullets)
	{
		b->Draw(renderer, interp);
	}
}

void BulletSystem::AddBullet(std::shared_ptr<Bullet> bullet)
{
	this->bullets.push_back(bullet);
}

void BulletSystem::EraseBullets()
{
	this->bullets.erase(
		std::remove_if(
			this->bullets.begin(), this->bullets.end(),
			[this](std::shared_ptr<Bullet>& b) -> bool {
				return b->isSpent();
			}),
		this->bullets.end());
}