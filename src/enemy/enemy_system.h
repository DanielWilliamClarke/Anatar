#ifndef ENEMY_SYSTEM_H
#define ENEMY_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <map>

#include "quad_tree/quad_tree.h"

class Entity;
struct EntityCollision;
class IEnemyTypeFactory;

typedef QuadTree<std::shared_ptr<Entity>, EntityCollision> CollisionQuadTree;

class EnemySystem: public std::enable_shared_from_this<EnemySystem>
{
public:
	EnemySystem();
	virtual ~EnemySystem() = default;

	void Update(std::shared_ptr<CollisionQuadTree> quadTree, float dt);
	void Draw(sf::RenderTarget& target, float interp) const;

	virtual std::shared_ptr<EnemySystem> AddFactory(float spawnInterval, std::shared_ptr<IEnemyTypeFactory> factory);

	std::vector<std::shared_ptr<Entity>>& GetEnemies();

private:
	std::vector<std::shared_ptr<Entity>> enemies;
	std::map<float, std::vector<std::shared_ptr<IEnemyTypeFactory>>> factories;

	float accumulator;
	float maxInterval;

	float maxEnemies;
};

#endif //ENEMY_SYSTEM_H