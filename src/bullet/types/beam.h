#ifndef BEAM_H
#define BEAM_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet/bullet.h"

class IRayCaster;

class Beam : public Bullet
{
public:
	Beam(BulletTrajectory& trajectory, BulletConfig config, std::shared_ptr<IRayCaster> rayCaster, sf::FloatRect bounds, float damageRate);
	virtual ~Beam() = default;

	virtual void Update(float dt, float worldSpeed) override;
	virtual void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp) override;
	virtual std::vector<EntityCollision> DetectCollisions(std::vector<std::shared_ptr<Entity>> targets) override;

	void Reignite();

protected:
	std::shared_ptr<IRayCaster> rayCaster;
	std::shared_ptr<sf::RectangleShape> round;
	std::shared_ptr<sf::Vector2f> collisionPosition;
	sf::FloatRect bounds;

	sf::Clock damageClock;
	float damageRateAccumulator;
	float damageRate;
	float damageCache;
};

#endif // BEAM_H
