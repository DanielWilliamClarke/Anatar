#include "offset_movement_component.h"

OffSetMovementComponent::OffSetMovementComponent(sf::Vector2f offset)
	: offset(offset) 
{}

sf::Vector2f OffSetMovementComponent::Integrate(sf::Vector2f origin, const float& dt) const
{
	return origin + offset;
}

sf::Vector2f OffSetMovementComponent::Interpolate(sf::Vector2f interpPosition) const
{
	return interpPosition + offset;
}