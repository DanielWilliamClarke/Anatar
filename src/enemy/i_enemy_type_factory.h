#ifndef I_ENEMY_TYPE_FACTORY_H
#define I_ENEMY_TYPE_FACTORY_H
#pragma once

#include <memory>

template<typename T>
class Entity;

template<typename T>
class IEnemyTypeFactory
{
public:
	IEnemyTypeFactory() = default;
	virtual ~IEnemyTypeFactory() = default;
	virtual std::shared_ptr<Entity<T>> Create() = 0;
};

#endif //I_ENEMY_TYPE_FACTORY_H