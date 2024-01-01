#include "bullet_system.h"

#include <algorithm>

#include "types/projectile.h"

#include "i_bullet_factory.h"

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

void BulletSystem::Update(const CollisionQuadTree& quadTree, float dt, float worldSpeed)
{
	this->EraseBullets();

	// Determine collisions to resolve
	std::vector<std::shared_ptr<Collision>> unresolved;
	for (auto& b : this->bullets)
	{
		b->Update(dt, worldSpeed);

		auto collisions = b->DetectCollisions(quadTree);
		if (!collisions.empty() && b->GetDamage() > 0.0f)
		{
			unresolved.reserve(std::max(unresolved.capacity(), unresolved.size() + collisions.size()));
			unresolved.insert(unresolved.end(), collisions.begin(), collisions.end());
		}
	}

	BulletSystem::ResolveCollisions(unresolved);
}

void BulletSystem::Draw(const std::shared_ptr<IRenderer>& renderer, float interp)
{
	for (auto& b : this->bullets)
	{
		b->Draw(renderer, interp);
	}
}

void BulletSystem::AddBullet(const std::shared_ptr<Bullet>& bullet)
{
	this->bullets.push_back(bullet);
}

void BulletSystem::EraseBullets()
{
    std::erase_if(this->bullets, [this](std::shared_ptr<Bullet>& b) -> bool {
        return b->isSpent();
    });
}

void BulletSystem::ResolveCollisions(const std::vector<std::shared_ptr<Collision>>& collisions)
{
    for(const auto& c : collisions)
    {
        auto damage = c->bullet->GetDamage();
        c->bullet->GetCollisionResolver()(
            c->target->payload->resolver(damage, c->collisionPosition),
            damage
        );
    }
}