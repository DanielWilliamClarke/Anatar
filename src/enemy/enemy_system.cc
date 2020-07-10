#include "enemy_system.h"

#include <algorithm>

#include "enemy.h"
#include "i_enemy_type_factory.h"
#include "../entity/entity_object.h"
#include "../entity/entity.h"

EnemySystem::EnemySystem() 
	: accumulator(0), maxInterval(0)
{}

void EnemySystem::Update(float dt) 
{
	// Create enemies
	this->accumulator += dt;

	for (auto& f : factories)
	{
		if (std::fmod(this->accumulator, f.first) < dt)
		{
			for (auto& fe : f.second)
			{
				enemies.push_back(fe->Create());
			}
		}
	}

	if (this->accumulator >= this->maxInterval) {
		this->accumulator -= this->maxInterval;
	}

	// Remove enemies
	enemies.remove_if([=](std::shared_ptr<Entity> e) -> bool {
		auto enemySprite = e->GetObject("enemy")->GetSprite();
		auto enemyBounds = enemySprite->getGlobalBounds();
		auto enemyX = enemySprite->getPosition().x + enemyBounds.width;
		return enemyX <= 0 || e->HasDied();
	});

	// Update all remaining enemies
	for (auto& e : enemies)
	{
		e->Update(dt);
	}
}

void EnemySystem::Draw(sf::RenderTarget& target, float interp) const
{
	for (auto& e : enemies)
	{
		e->Draw(target, interp);
	}
}

std::shared_ptr<EnemySystem> EnemySystem::AddFactory(float spawnInterval, std::shared_ptr<IEnemyTypeFactory> factory)
{
	this->factories[spawnInterval].push_back(factory);
	if (spawnInterval > this->maxInterval) {
		this->maxInterval = spawnInterval;
	}
	return shared_from_this();
}

std::list<std::shared_ptr<Entity>>& EnemySystem::GetEnemies()
{
	return enemies;
}