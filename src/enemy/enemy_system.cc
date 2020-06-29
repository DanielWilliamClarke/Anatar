#include "enemy_system.h"

#include <algorithm>

#include "enemy.h"
#include "i_enemy_type_factory.h"
#include "../entity/entity_object.h"

EnemySystem::EnemySystem() 
	: accumulator(0) 
{}

void EnemySystem::Update(float dt) 
{
	// Create enemies
	this->accumulator += dt;

	for (auto& f : factories)
	{
		auto diff = std::abs(f.first - this->accumulator);
		if (diff <= 0.001)
		{
			enemies.push_back(f.second->Create());	
		}
	}

	if (this->accumulator > this->maxInterval) {
		this->accumulator = 0;
	}

	// Remove enemies
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(), [=](std::shared_ptr<Enemy> e) -> bool {
			return e->GetObject("enemy")->GetSprite()->getPosition().x <= 0;
			}),
		enemies.end());

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
	this->factories[spawnInterval] = factory;
	if (spawnInterval > this->maxInterval) {
		this->maxInterval = spawnInterval;
	}
	return shared_from_this();
}