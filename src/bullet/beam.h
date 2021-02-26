#ifndef BEAM_H
#define BEAM_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet.h"

class Beam : public Bullet
{
public:
	Beam(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config, sf::FloatRect bounds);
	virtual ~Beam() = default;

	virtual void Update(float dt, float worldSpeed) override;
	virtual void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp) override;
	virtual void CollisionDetected(sf::Vector2f point) override;
	virtual std::shared_ptr<sf::Shape> GetRound() const override;

protected:
	std::shared_ptr<sf::RectangleShape> round;
	sf::Vector2f collisionPosition;
	sf::FloatRect bounds;
};

#endif // BEAM_H
