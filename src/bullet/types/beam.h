#ifndef BEAM_H
#define BEAM_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet/bullet.h"

class IRayCaster;

struct Collision;
template<typename C>
class QuadTree;

class Beam : public Bullet
{
public:
	Beam(BulletTrajectory& trajectory, BulletConfig& config, std::shared_ptr<IRayCaster> rayCaster, sf::FloatRect bounds, float damageRate);
	virtual ~Beam() = default;

	virtual void Update(float dt, float worldSpeed) override;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) override;
	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(std::shared_ptr<QuadTree<Collision>> quadTree) override;

	void Reignite();
	void Cease();

protected:
	std::shared_ptr<IRayCaster> rayCaster;
	std::shared_ptr<sf::RectangleShape> round;
	std::shared_ptr<sf::Vector2f> collisionPosition;
	sf::FloatRect bounds;

	float damageRateAccumulator;
	float damageRate;
	float damageCache;
};

#endif // BEAM_H
