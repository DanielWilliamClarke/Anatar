#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "i_bullet_system.h"

class Bullet;
struct BulletConfig;
class Entity;
class IGlowShaderRenderer;
class IWeaponComponent;

struct BulletSystemDebrisConfig
{
	std::shared_ptr<BulletConfig> onDeath;
	std::shared_ptr<BulletConfig> onCollision;

	BulletSystemDebrisConfig(std::shared_ptr<BulletConfig> onDeath, std::shared_ptr<BulletConfig> onCollision)
		: onDeath(onDeath), onCollision(onCollision)
	{}
};

class BulletSystem : public IBulletSystem
{
public:
	enum affinities { LEFT = -1, RIGHT = 1 };

	BulletSystem(sf::FloatRect bounds, int affinity, std::shared_ptr<IWeaponComponent> debrisGenerator = nullptr, std::shared_ptr<BulletSystemDebrisConfig> debrisConfigs = nullptr);
	virtual ~BulletSystem() = default;

	virtual void FireBullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config) override;

	void Update(float dt, float worldSpeed, std::list<std::shared_ptr<Entity>>& collisionTargets);
	void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp);

private:
	std::list<std::unique_ptr<Bullet>> bullets;
	std::shared_ptr<IWeaponComponent> debrisGenerator;
	std::shared_ptr<BulletSystemDebrisConfig> debrisConfigs;
	sf::FloatRect bounds;
	int affinity;
};

#endif // BULLET_SYSTEM_H