#ifndef ENEMY_TYPE_FACTORY_H
#define ENEMY_TYPE_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "i_enemy_type_factory.h"
#include "enemy.h"

#include "../bullet/i_bullet_system.h"

class IWeaponComponentFactory;
class ILocalMovementComponent;

struct EnemyWeaponConfig
{
	std::shared_ptr<IWeaponComponentFactory> weaponComponentFactory;
	std::shared_ptr<IBulletSystem> bulletSystem;
	float delay;

	EnemyWeaponConfig(std::shared_ptr<IWeaponComponentFactory> weaponComponentFactory, std::shared_ptr<IBulletSystem> bulletSystem, float delay)
		: weaponComponentFactory(weaponComponentFactory), bulletSystem(bulletSystem), delay(delay)
	{}
};

struct EnemyMotionConfig
{
	sf::FloatRect bounds;
	float worldSpeed;
	float enemySpeed;

	EnemyMotionConfig(sf::FloatRect bounds, float worldSpeed, float enemySpeed)
		: bounds(bounds), worldSpeed(worldSpeed), enemySpeed(enemySpeed)
	{}
};

struct EnemyAnimationConfig
{
	std::shared_ptr<sf::Texture> texture;
	int frames;
	float frameDuration;
	float scale;

	EnemyAnimationConfig(std::shared_ptr<sf::Texture> texture, int frames, float frameDuration, float scale)
		: texture(texture), frames(frames), frameDuration(frameDuration), scale(scale)
	{}
};

struct EnemyConfig
{
	std::function<EntityManifest(EnemyConfig)> builder;
	EnemyMotionConfig motionConfig;
	EnemyAnimationConfig animationConfig;
	EnemyWeaponConfig weaponConfig;

	EnemyConfig(std::function<EntityManifest(EnemyConfig)> builder, EnemyMotionConfig motionConfig, EnemyAnimationConfig animationConfig, EnemyWeaponConfig weaponConfig)
		: builder(builder), motionConfig(motionConfig), animationConfig(animationConfig), weaponConfig(weaponConfig)
	{}
};

class EnemyTypeFactory : public IEnemyTypeFactory, public Enemy
{
public:
	EnemyTypeFactory(EnemyConfig config);
	virtual ~EnemyTypeFactory() = default;
	virtual std::shared_ptr<Entity> Create() override;

	// Builder methods
	static EntityManifest BuildLinearEnemy(EnemyConfig config);
	static EntityManifest BuildOribitalEnemy(EnemyConfig config);

private:

	static EntityManifest BuildEnemy(EnemyConfig config, std::shared_ptr<ILocalMovementComponent> movementComponent);
	EnemyConfig config;
};

#endif //I_ENEMY_TYPE_FACTO