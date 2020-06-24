#ifndef OFFSET_MOVEMENT_COMPONENT_H
#define OFFSET_MOVEMENT_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "i_local_movement_component.h"

class OffSetMovementComponent : public ILocalMovementComponent
{
public:
	OffSetMovementComponent(sf::Vector2f offset);
	virtual ~OffSetMovementComponent() = default;

	virtual sf::Vector2f Integrate(sf::Vector2f origin, const float& dt);
	virtual sf::Vector2f Interpolate(sf::Vector2f interpPosition) const;

protected:
	sf::Vector2f offset;
};

#endif OFFSET_MOVEMENT_COMPONENT_H