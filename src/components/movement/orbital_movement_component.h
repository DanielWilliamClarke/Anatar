#ifndef ORBITAL_MOVEMENT_COMPONENT_H
#define ORBITAL_MOVEMENT_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "i_local_movement_component.h"

class OrbitalMovementComponent : public ILocalMovementComponent
{
public:
	OrbitalMovementComponent(sf::Vector2f offset, float radius, float speed);
	virtual ~OrbitalMovementComponent() = default;

	virtual sf::Vector2f Integrate(sf::Vector2f origin, const float& dt);
	virtual sf::Vector2f Interpolate(sf::Vector2f interpPosition) const;

private:
	sf::Vector2f polarCoordinate;
	sf::Vector2f offset;
	float radius;
	float angle;
	float speed;
};

#endif //ORBITAL_MOVEMENT_COMPONENT_H