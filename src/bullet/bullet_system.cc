#include "bullet_system.h"

#include <thread>

#include "bullet.h"

#include "../entity/entity.h"

#include "../components/weapon/i_weapon_component.h"

BulletSystem::BulletSystem(sf::FloatRect bounds, int affinity, std::shared_ptr<IWeaponComponent> debrisGenerator, std::shared_ptr<BulletConfig> debrisConfig)
	:  bounds(bounds), affinity(affinity), debrisGenerator(debrisGenerator), debrisConfig(debrisConfig)
{}

void BulletSystem::FireBullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
{
	auto alignedVelocity = sf::Vector2f(velocity.x * (float)affinity, velocity.y);
	this->bullets.push_back(std::make_shared<Bullet>(position, alignedVelocity, config));
}

void BulletSystem::Update(float dt, float worldSpeed, std::list<std::shared_ptr<Entity>>& collisionTargets)
{
	const auto maxThreads = bullets.size() < 8 ? bullets.size() : 8;

	if (maxThreads > 0)
	{
		auto totalBullets = bullets.size();
		auto bulletsPerThread = (int)ceil(bullets.size() / maxThreads);

		auto bulletsIter = bullets.begin();
		std::vector<std::list<std::shared_ptr<Bullet>>> threadBullets;
		threadBullets.resize(maxThreads);
		for (auto i = 0; i < totalBullets; i++)
		{
			auto index = i % maxThreads;
			threadBullets[index].push_back((*bulletsIter));
			std::advance(bulletsIter, 1);
		}

		std::thread* t = new std::thread[maxThreads];
		for (auto i = 0; i < maxThreads; i++)
		{
			t[i] = std::thread(
				[=](std::list<std::shared_ptr<Bullet>> tBullets, std::list<std::shared_ptr<Entity>>& collisionTargets) {
					for (auto& b : tBullets)
					{
						b->Update(dt, worldSpeed);

						for (auto& c : collisionTargets)
						{
							if (c->DetectCollision(b->GetRound()->getGlobalBounds()))
							{
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
										debrisGenerator->Fire(b->GetPosition(), *debrisConfig);
									}
								}

								// spend round 
								if (!damage.second)
								{
									b->CollisionDetected();
								}
							}
						}
					}
				}, threadBullets[i], collisionTargets);
		}

		for (auto i = 0; i < maxThreads; i++)
		{
			if (t[i].joinable())
			{
				t[i].join();
			}
		}
	}

	// Update and perform collision detection
	

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
