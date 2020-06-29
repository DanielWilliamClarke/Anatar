#include "orbital_movement_component.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

OrbitalMovementComponent::OrbitalMovementComponent(sf::Vector2f offset, float radius, float speed)
	: OffSetMovementComponent{ offset }, radius(radius), speed(speed), angle(0.0f)
{}

sf::Vector2f OrbitalMovementComponent::Integrate(sf::Vector2f origin, const float& dt)
{
	const auto radAngle = angle * (float)(M_PI / 180);

	angle += speed * dt;
	if (angle >= 360.0f) {
		angle = 0.0f;
	}

	polarCoordinate = sf::Vector2f(
		radius * (std::cos(radAngle)),
		radius * (std::sin(radAngle)));

	return origin + offset + polarCoordinate;
}

sf::Vector2f OrbitalMovementComponent::Interpolate(sf::Vector2f interpPosition) const
{
	return interpPosition + offset + polarCoordinate;
}