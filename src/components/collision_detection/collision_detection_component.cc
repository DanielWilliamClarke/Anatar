#include "collision_detection_component.h"

#include "util/i_ray_caster.h"

CollisionDetectionComponent::CollisionDetectionComponent(std::shared_ptr<IRayCaster> rayCaster) 
	: rayCaster(rayCaster)
{}

std::shared_ptr<sf::Vector2f> CollisionDetectionComponent::DetectCollision(const sf::FloatRect& box, const sf::Vector2f& position, bool ray, const sf::Vector2f& dir) const
{
	if (!ray && box.contains(position))
	{
		return std::make_shared<sf::Vector2f>(position);
	}

	auto intersection = this->rayCaster->RayBoxIntersects(position, dir, box);
	if (intersection->intersects)
	{
		return std::make_shared<sf::Vector2f>(intersection->point);
	}

	return nullptr;
}

bool CollisionDetectionComponent::DetectIntersection(const sf::FloatRect& boxA, const sf::FloatRect& boxB) const
{
	return boxA.intersects(boxB);
}