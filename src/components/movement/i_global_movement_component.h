#ifndef I_GLOBAL_MOVEMENT_COMPONENT_H
#define I_GLOBAL_MOVEMENT_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

struct Input;

class IGlobalMovementComponent
{
public:
	IGlobalMovementComponent() = default;
	virtual ~IGlobalMovementComponent() = default;

	virtual void SetEntityAttributes(sf::Vector2f position, sf::FloatRect entityBounds) = 0;
	virtual const sf::Vector2f GetPosition() const = 0;
	virtual const sf::Vector2f GetCenter() const = 0;
	
	virtual sf::Vector2f Integrate(Input& in, const float& dt) = 0;
	virtual sf::Vector2f Integrate(const float& dt) = 0;
	virtual sf::Vector2f Interpolate(const float& interp) = 0;
};

#endif //I_GLOBAL_MOVEMENT_COMPONENT_H