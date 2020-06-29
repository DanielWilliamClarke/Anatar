#ifndef ENEMY_TYPE_FACTORY_H
#define ENEMY_TYPE_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "i_enemy_type_factory.h"
#include "enemy.h"

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
	std::string textureFile;
	int frames;
	float frameDuration;
	float scale;

	EnemyAnimationConfig(std::string textureFile, int frames, float frameDuration, float scale)
		: textureFile(textureFile), frames(frames), frameDuration(frameDuration), scale(scale)
	{}
};

struct EnemyConfig
{
	std::function<EntityManifest(EnemyConfig)> builder;
	EnemyMotionConfig motionConfig;
	EnemyAnimationConfig animationConfig;

	EnemyConfig(std::function<EntityManifest(EnemyConfig)> builder, EnemyMotionConfig motionConfig, EnemyAnimationConfig animationConfig)
		: builder(builder), motionConfig(motionConfig), animationConfig(animationConfig)
	{}
};

class EnemyTypeFactory : public IEnemyTypeFactory, public Enemy
{
public:
	EnemyTypeFactory(EnemyConfig config);
	virtual ~EnemyTypeFactory() = default;
	virtual std::shared_ptr<Enemy> Create() override;

	// Builder methods
	static EntityManifest BuildLinearEnemy(EnemyConfig config);
	static EntityManifest BuildOribitalEnemy(EnemyConfig config);
private:
	EnemyConfig config;
};

#endif //I_ENEMY_TYPE_FACTO