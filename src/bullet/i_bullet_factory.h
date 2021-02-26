#ifndef I_BULLET_FACTORY_H
#define I_BULLET_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet;

class IBulletFactory
{
public:
	IBulletFactory() = default;
	virtual ~IBulletFactory() = default;

	virtual std::shared_ptr<Bullet> Construct(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config) const = 0;
};

#endif // I_BULLET_SYSTEM_H
