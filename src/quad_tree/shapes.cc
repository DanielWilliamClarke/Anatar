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

CircleQuery::CircleQuery(sf::Vector2f origin, float r)
	: origin(origin), r(r), rSq(r* r)
{}

bool CircleQuery::Intersects(sf::FloatRect range) const
{
	auto xDist = abs(range.left - this->origin.x);
	auto yDist = abs(range.top - this->origin.y);

	auto xEdgeDist = xDist - range.width;
	auto yEdgeDist = yDist - range.height;

	auto edges = xEdgeDist * xEdgeDist + yEdgeDist * yEdgeDist;

	if (xDist > (this->r + range.width) || yDist > (this->r + range.height)) {
		return false;
	}

	if (xDist <= range.width || yDist <= range.height) {
		return true;
	}

	return edges < this->rSq;
}

RayQuery::RayQuery(std::shared_ptr<IRayCaster> rayCaster, sf::Vector2f origin, sf::Vector2f direction)
	: rayCaster(rayCaster), origin(origin), direction(direction)
{}

bool RayQuery::Intersects(sf::FloatRect range) const
{
	return this->rayCaster->RayBoxIntersects(origin, direction, range)->intersects;
}