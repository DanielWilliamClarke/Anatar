#ifndef I_BULLET_SYSTEM_H
#define I_BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
struct BulletConfig;
class IBulletFactory;

class IBulletSystem
{
public:
	IBulletSystem() = default;
	virtual ~IBulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config) = 0;
};

#endif // I_BULLET_SYSTEM_H
