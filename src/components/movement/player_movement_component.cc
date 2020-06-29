#include <math.h>
#include <iostream>
#include "player_movement_component.h"
#include "../../player/player_input.h"

PlayerMovementComponent::PlayerMovementComponent(sf::FloatRect bounds, float& worldSpeed)
	: bounds(bounds),
	entityBounds(sf::FloatRect(0, 0, 0, 0)),
	movementSpeed(worldSpeed / 4),
	worldSpeed(worldSpeed),
	worldVelocity(sf::Vector2f(-worldSpeed, 0)),
	velocity(sf::Vector2f(.0f, .0f)),
	gravity(sf::Vector2f(.0f, 9.81f)),
	thrust(sf::Vector2f(.0f, -9.81f)),
	maxThrust(sf::Vector2f(.0f, -9.81f)),
	mass(1.0f),
	force(.0f)

{
}

const sf::Vector2f PlayerMovementComponent::GetPosition() const
{
	return this->position;
}

const sf::Vector2f PlayerMovementComponent::GetCenter() const
{
	return sf::Vector2f(
		this->bounds.width / 2,
		this->bounds.height / 2);
}

const sf::FloatRect PlayerMovementComponent::GetBounds() const
{
	return this->bounds;
}

void PlayerMovementComponent::SetEntityAttributes(sf::Vector2f position, sf::FloatRect bounds)
{
	this->position = position;
	this->entityBounds = bounds;
}

sf::Vector2f PlayerMovementComponent::Integrate(Input& in, const float& dt)
{
	lastPosition = position;
	if (in.falling)
	{
		thrust = sf::Vector2f(0.0f, 0.0f);
	}
	else
	{
		thrust = maxThrust;
	}

	auto inputForce = in.movement * movementSpeed;
	auto force = gravity + thrust + inputForce;
	auto acceleration = force / mass; // 2nd derivative
	velocity += acceleration * dt; // 1st derivative
	position = Bound(position + velocity + worldVelocity * dt);

	return position;
}

sf::Vector2f PlayerMovementComponent::Interpolate(const float& interp)
{
	return position * interp + lastPosition * (1.0f - interp);
}

sf::Vector2f PlayerMovementComponent::Bound(sf::Vector2f newPosition)
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

