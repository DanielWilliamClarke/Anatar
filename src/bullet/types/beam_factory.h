#ifndef BEAM_FACTORY_H
#define BEAM_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>

#include "bullet/i_bullet_factory.h"
#include "beam.h"
#include "bullet/bullet.h"
#include "util/i_ray_caster.h"

class BeamFactory : public IBulletFactory
{
public:
	BeamFactory(std::shared_ptr<IRayCaster> rayCaster, sf::FloatRect bounds, float damageRate)
		: rayCaster(rayCaster), bounds(bounds), damageRate(damageRate)
	{}

	virtual ~BeamFactory() = default;

	virtual std::shared_ptr<Bullet> Construct(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config) const override {
		return std::make_shared<Beam>(position, velocity, config, rayCaster, bounds, damageRate);
	};

private:
	std::shared_ptr<IRayCaster> rayCaster;
	sf::FloatRect bounds;
	float damageRate;
};

#endif //BEAM_FACTORY_H