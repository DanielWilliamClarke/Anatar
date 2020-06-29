#ifndef I_ENEMY_TYPE_FACTORY_H
#define I_ENEMY_TYPE_FACTORY_H
#pragma once

#include <memory>

class Enemy;

class IEnemyTypeFactory
{
public:
	IEnemyTypeFactory() = default;
	virtual ~IEnemyTypeFactory() = default;
	virtual std::shared_ptr<Enemy> Create() = 0;
};

#endif //I_ENEMY_TYPE_FACTORY_H