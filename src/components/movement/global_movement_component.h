#ifndef GLOBAL_MOVEMENT_COMPONENT_H
#define GLOBAL_MOVEMENT_COMPONENT_H

#pragma once
#include <SFML/Graphics.hpp>

#include "i_global_movement_component.h"

struct Input;

class GlobalMovementComponent: public IGlobalMovementComponent
{
public:

	GlobalMovementComponent(sf::FloatRect bounds);
	virtual ~GlobalMovementComponent() = default;

	virtual void SetEntityAttributes(sf::Vector2f position, sf::FloatRect entityBounds);
	virtual const sf::Vector2f GetPosition() const;
	virtual const sf::Vector2f GetCenter() const; 

	virtual sf::Vector2f Integrate(Input in, const float& dt);
	virtual sf::Vector2f Interpolate(const float& interp);

private:
	
	sf::Vector2f Bound(sf::Vector2f newPosition);

	// Sprite Position
	sf::Vector2f position;
	sf::Vector2f lastPosition;

	// Physics
	sf::Vector2f gravity;
	sf::Vector2f maxThrust;
	sf::Vector2f thrust;
	sf::Vector2f velocity;
	float force;
	float mass;
	float movementSpeed;

	// Bounds checking
	sf::FloatRect bounds;
	sf::FloatRect entityBounds;
};

#endif //GLOBAL_MOVEMENT_COMPONENT_H