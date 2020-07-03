#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "i_bullet_system.h"

class Bullet;
class Entity;

class BulletSystem : public IBulletSystem
{
public:
	enum affinities { LEFT = -1, RIGHT = 1 };

	BulletSystem(sf::FloatRect bounds, int affinity);
	virtual ~BulletSystem() = default;

	virtual void FireBullet(sf::Vector2f position, sf::Vector2f velocity, sf::Color colour, float radius) override;

	void Update(float dt, float worldSpeed, std::list<std::shared_ptr<Entity>> collisionTargets);
	void Draw(sf::RenderTarget& target, float interp);

private:
	std::list <Bullet> bullets;
	sf::FloatRect bounds;
	int affinity;
};

#endif // BULLET_SYSTEM_H