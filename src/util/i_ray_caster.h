#ifndef I_RAY_CASTER_H
#define I_RAY_CASTER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

struct RayIntersection {
	bool intersects;
	sf::Vector2f point;

	RayIntersection(bool intersects, sf::Vector2f point = sf::Vector2f())
		: intersects(intersects), point(point)
	{}
};

class IRayCaster
{
public:
	IRayCaster() = default;
	virtual ~IRayCaster() = default;
	virtual std::shared_ptr<RayIntersection> RayBoxIntersects(const sf::Vector2f& origin, const sf::Vector2f& direction, sf::FloatRect box) const = 0;
};

#endif // I_RAY_CASTER_H