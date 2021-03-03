#ifndef ENEMY_SYSTEM_H
#define ENEMY_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <map>

class Entity;
class IEnemyTypeFactory;

class EnemySystem: public std::enable_shared_from_this<EnemySystem>
{
public:
	EnemySystem();
	virtual ~EnemySystem() = default;

	void Update(float dt);
	void Draw(sf::RenderTarget& target, float interp) const;

	virtual std::shared_ptr<EnemySystem> AddFactory(float spawnInterval, std::shared_ptr<IEnemyTypeFactory> factory);

	std::vector<std::shared_ptr<Entity>>& GetEnemies();

private:
	std::vector<std::shared_ptr<Entity>> enemies;
	std::map<float, std::vector<std::shared_ptr<IEnemyTypeFactory>>> factories;

	sf::Clock spawnClock;
	float accumulator;
	float maxInterval;

	float maxEnemies;
};

#endif //ENEMY_SYSTEM_H