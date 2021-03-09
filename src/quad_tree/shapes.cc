#include "shapes.h"

#include "util/math_utils.h"
#include "util/i_ray_caster.h"

RectangleQuery::RectangleQuery(sf::FloatRect rect)
	: rect(rect)
{}

bool RectangleQuery::Intersects(sf::FloatRect range) const
{
	return range.intersects(this->rect);
}

sf::FloatRect RectangleQuery::Get() const
{
	return this->rect;
}

RayQuery::RayQuery(std::shared_ptr<IRayCaster> rayCaster, sf::Vector2f origin, sf::Vector2f direction)
	: rayCaster(rayCaster), origin(origin), direction(direction)
{}

bool RayQuery::Intersects(sf::FloatRect range) const
{
	return this->rayCaster->RayBoxIntersects(origin, direction, range)->intersects;
}