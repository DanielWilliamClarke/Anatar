#ifndef RAY_CASTER_H
#define RAY_CASTER_H
#pragma once

#include "i_ray_caster.h"

class RayCaster : public IRayCaster
{
public:
	RayCaster() = default;
	virtual ~RayCaster() = default;
	virtual std::shared_ptr<RayIntersection> RayBoxIntersects(const sf::Vector2f& origin, const sf::Vector2f& direction, sf::FloatRect box) const override;
};

#endif // I_RAY_CASTER_H