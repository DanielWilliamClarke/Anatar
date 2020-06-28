#ifndef ENEMY_BUILDER_H
#define ENEMY_BUILDER_H
#pragma once

#include <memory>

#include "../entity/i_entity_builder.h"
#include "enemy.h"

class EntityObject;

class EnemyBuilder : public IEntityObjectBuilder, public Enemy
{
public:
	EnemyBuilder() = default;
	virtual ~EnemyBuilder() = default;
	virtual EntityManifest Build() override;
private:
	void BuildEnemy();

	EntityManifest manifest;
};

#endif //ENEMY_BUILDER_H