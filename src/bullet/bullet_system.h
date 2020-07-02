#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "i_bullet_system.h"

class Bullet;
class Entity;

class BulletSystem: public IBulletSystem
{
public:
	BulletSystem(sf::FloatRect bounds, std::list<std::shared_ptr<Entity>> collisionTargets);
	virtual ~BulletSystem() = default;

	virtual void FireBullet(sf::Vector2f position, sf::Vector2f velocity, sf::Color colour, float radius) override;

	void Update(float dt, float worldSpeed);
	void Draw(sf::RenderTarget& target, float interp);

private:
	std::list <Bullet> bullets;
	sf::FloatRect bounds;
	std::list<std::shared_ptr<Entity>> collisionTargets;
};

#endif // BULLET_SYSTEM_H
