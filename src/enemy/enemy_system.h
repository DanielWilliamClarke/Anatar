#ifndef ENEMY_SYSTEM_H
#define ENEMY_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <list>
#include <unordered_map>

#include "enemy/enemy.h"

template <typename T>
class IEnemyTypeFactory;

class IRenderer;

class EnemySystem: public std::enable_shared_from_this<EnemySystem>
{
public:
	EnemySystem();
	virtual ~EnemySystem() = default;

	void Update(const CollisionQuadTree& quadTree, float dt);
	void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) const;

	virtual std::shared_ptr<EnemySystem> AddFactory(float spawnInterval, const std::shared_ptr<IEnemyTypeFactory<EnemyObjects>>& factory);
	std::vector<std::shared_ptr<Entity<EnemyObjects>>>& GetEnemies();
private:
	std::vector<std::shared_ptr<Entity<EnemyObjects>>> enemies;
	std::unordered_map<float, std::vector<std::shared_ptr<IEnemyTypeFactory<EnemyObjects>>>> factories;

	float accumulator;
	float maxInterval;

	float maxEnemies;
};

#endif //ENEMY_SYSTEM_H