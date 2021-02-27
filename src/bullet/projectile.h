#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet.h"

class Projectile : public Bullet
{
public:
	Projectile(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config);
	virtual ~Projectile() = default;

	virtual void Update(float dt, float worldSpeed) override;
	virtual void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp) override;
	virtual void CollisionDetected(sf::Vector2f* point) override;
	virtual std::shared_ptr<sf::Shape> GetRound() const override; 

private:
	std::shared_ptr<sf::Shape> round; // Holds the bullet shape / position etc
};

#endif // PROJECTILE_H
