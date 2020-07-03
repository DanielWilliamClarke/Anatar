#ifndef I_BULLET_SYSTEM_H
#define I_BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>

struct BulletConfig;

class IBulletSystem
{
public:
	IBulletSystem() = default;
	virtual ~IBulletSystem() = default;

	virtual void FireBullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config) = 0;
};

#endif // I_BULLET_SYSTEM_H
