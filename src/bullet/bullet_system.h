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

class BulletSystem : public IBulletSystem
{
public:
	enum affinities { LEFT = -1, RIGHT = 1 };

	BulletSystem(sf::FloatRect bounds, int affinity);
	virtual ~BulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config) override;
	void Update(float dt, float worldSpeed, std::vector<std::shared_ptr<Entity>>& collisionTargets);
	void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp);

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::FloatRect bounds;
	int affinity;
};

#endif // BULLET_SYSTEM_H