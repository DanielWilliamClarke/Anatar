#ifndef I_BULLET_SYSTEM_H
#define I_BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>

class IBulletSystem
{
public:
	IBulletSystem() = default;
	virtual ~IBulletSystem() = default;

	virtual void FireBullet(sf::Vector2f position, sf::Vector2f velocity, sf::Color colour, float radius) = 0;
};

#endif // I_BULLET_SYSTEM_H
