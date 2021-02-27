#ifndef BEAM_FACTORY_H
#define BEAM_FACTORY_H
#pragma once

#include <SFML/Graphics.hpp>

#include "i_bullet_factory.h"
#include "beam.h"
#include "bullet.h"

class BeamFactory : public IBulletFactory
{
public:
	BeamFactory(sf::FloatRect bounds, float damageRate)
		: bounds(bounds), damageRate(damageRate)
	{}

	virtual ~BeamFactory() = default;

	virtual std::shared_ptr<Bullet> Construct(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config) const override {
		return std::make_shared<Beam>(position, velocity, config, bounds, damageRate);
	};

private:
	sf::FloatRect bounds;
	float damageRate;
};

#endif //BEAM_FACTORY_H