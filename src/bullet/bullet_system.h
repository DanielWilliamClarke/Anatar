#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
class Entity;

class BulletSystem
{
public:
	BulletSystem(sf::FloatRect bounds, std::vector<std::shared_ptr<Entity>> collisionTargets);
	virtual ~BulletSystem() = default;

	void FireBullet(sf::Vector2f position, sf::Vector2f velocity, sf::Color colour, float radius);

	void Update(float dt, float worldSpeed);
	void Draw(sf::RenderTarget& target, float interp);

private:
	std::vector<Bullet> bullets;
	sf::FloatRect bounds;
	std::vector<std::shared_ptr<Entity>> collisionTargets;
};

#endif // BULLET_SYSTEM_H
