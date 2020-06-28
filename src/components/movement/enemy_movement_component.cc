#include <math.h>
#include <iostream>
#include "enemy_movement_component.h"

EnemyMovementComponent::EnemyMovementComponent(sf::FloatRect bounds, float& speed, float& worldSpeed)
	: bounds(bounds),
	velocity(sf::Vector2f(.0f, .0f)),
	gravity(sf::Vector2f(.0f, 9.81f)),
	thrust(sf::Vector2f(.0f, -9.81f)),
	maxThrust(sf::Vector2f(.0f, -9.81f)),
	mass(1.0f),
	force(.0f),
	movementSpeed(speed),
	worldSpeed(worldSpeed)
{
}

const sf::Vector2f EnemyMovementComponent::GetPosition() const
{
	return this->position;
}

const sf::Vector2f EnemyMovementComponent::GetCenter() const
{
	return sf::Vector2f(
		this->bounds.width / 2,
		this->bounds.height / 2);
}

void EnemyMovementComponent::SetEntityAttributes(sf::Vector2f position, sf::FloatRect entityBounds)
{
	this->position = position;
}

sf::Vector2f EnemyMovementComponent::Integrate(const float& dt)
{
	lastPosition = position;
	auto force = gravity + thrust;
	auto acceleration = force / mass; // 2nd derivative
	velocity += acceleration * dt; // 1st derivative
	sf::Vector2f worldVelocity(worldSpeed - movementSpeed, 0);
	position += velocity + worldVelocity * dt;
	return position;
}

sf::Vector2f EnemyMovementComponent::Interpolate(const float& interp)
{
	return position * interp + lastPosition * (1.0f - interp);
}
