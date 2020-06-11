#include <math.h>
#include <iostream>
#include "movement_component.h"
#include "player_input.h"

MovementComponent::MovementComponent(sf::FloatRect bounds)
	: bounds(bounds),
	entityBounds(sf::FloatRect(0, 0, 0, 0)),
	velocity(sf::Vector2f(.0f, .0f)),
	gravity(sf::Vector2f(.0f, 9.81f)),
	thrust(sf::Vector2f(.0f, -9.81f)),
	maxThrust(sf::Vector2f(.0f, -9.81f)),
	mass(0.01f),
	force(.0f),
	movementSpeed(5.0f)
{
}

const sf::Vector2f MovementComponent::GetPosition() const
{
	return this->position;
}

const sf::Vector2f MovementComponent::GetCenter() const
{
	return sf::Vector2f(
		this->bounds.width / 2,
		this->bounds.height / 2);
}

void MovementComponent::SetEntityAttributes(sf::Vector2f position, sf::FloatRect bounds)
{
	this->position = position;
	this->entityBounds = bounds;
}

sf::Vector2f MovementComponent::Integrate(Input in, const float& dt)
{
	lastPosition = position;

	if (in.falling)
	{
		thrust = sf::Vector2f(0.0f, 0.0f);
	}
	else
	{
		thrust = maxThrust;
		velocity.y = 0;
	}

	auto force = gravity + thrust;
	auto acceleration = force / mass; // 2nd derivative
	velocity += acceleration * dt; // 1st derivative
	auto scaledMovement = in.movement * movementSpeed;
	position = Bound(position + scaledMovement + velocity * dt);
	return position;
}

sf::Vector2f MovementComponent::Interpolate(const float& interp)
{
	return Bound(position * interp + lastPosition * (1.0f - interp));
}

sf::Vector2f MovementComponent::Bound(sf::Vector2f newPosition)
{
	if (newPosition.x <= bounds.left)
	{
		newPosition.x = bounds.left;
	}
	else if (newPosition.x + this->entityBounds.width >= bounds.width)
	{
		newPosition.x = bounds.width - this->entityBounds.width;
	}

	if (newPosition.y <= bounds.top)
	{
		newPosition.y = bounds.top;
	}
	else if (newPosition.y + this->entityBounds.height >= bounds.height)
	{
		newPosition.y = bounds.height - this->entityBounds.height;
		velocity.y = 0; // hit the bottom of the screen no need to fall further
	}
	return newPosition;
}

