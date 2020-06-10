#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
#include "movement_component.h"
#include "player_input.h"

MovementComponent::MovementComponent(sf::FloatRect bounds)
	: bounds(bounds), 
	velocity(sf::Vector2f(.0f, .0f)),
	gravity(sf::Vector2f(.0f, 9.81f)),
	thrust(sf::Vector2f(.0f, -9.81f)),
	maxThrust(sf::Vector2f(.0f, -9.81f)),
	mass(0.01f),
	force(.0f),
	movementSpeed(3.0f)
{
}

void MovementComponent::SetSprite(std::shared_ptr<sf::Sprite> sprite) {
	this->sprite = sprite;
	this->position = this->GetCenter();
	this->sprite->setPosition(this->position);
	lastPosition = position;
}

sf::Vector2f MovementComponent::GetCenter() const
{
	return sf::Vector2f(
		this->bounds.width / 2,
		this->bounds.height / 2);
}

const unsigned int MovementComponent::Integrate(Input in, const float& dt)
{
	lastPosition = position;
	position = IntegrateMovement(in, dt);
	sprite->setPosition(position);
	return CalculateDirection();
}

void MovementComponent::Interpolate(const float& interp)
{
	const auto positionInterp = Bound(position * interp + lastPosition * (1.0f - interp));
	sprite->setPosition(positionInterp);
}

sf::Vector2f MovementComponent::IntegrateMovement(Input in, const float& dt)
{
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
	return Bound(position + scaledMovement + velocity * dt);
}

sf::Vector2f MovementComponent::Bound(sf::Vector2f newPosition)
{
	const auto spriteBounds = sprite->getGlobalBounds();

	if (newPosition.x <= bounds.left)
	{
		newPosition.x = bounds.left;
	}
	else if (newPosition.x + spriteBounds.width >= bounds.width)
	{
		newPosition.x = bounds.width - spriteBounds.width;
	}

	if (newPosition.y <= bounds.top)
	{
		newPosition.y = bounds.top;
	}
	else if (newPosition.y + spriteBounds.height >= bounds.height)
	{
		newPosition.y = bounds.height - spriteBounds.height;
		velocity.y = 0; // hit the bottom of the screen no need to fall further
	}
	return newPosition;
}

const unsigned int MovementComponent::CalculateDirection() const 
{
	if (position != lastPosition) {

		const auto y = lastPosition.y - position.y;
		const auto x = lastPosition.x - position.x;
		const auto angle = std::atan2(y, x) * (180.0 / M_PI);
		const auto snappedAngle = std::round(angle / 90) * 90;

		if (snappedAngle == 0)
		{
			return MOVING_LEFT;
		}
		else if (snappedAngle == 90)
		{
			return MOVING_UP;
		} 
		else if (snappedAngle == 180)
		{
			return MOVING_RIGHT;
		}
		else if (snappedAngle == -90)
		{
			return MOVING_DOWN;
		}
	}

	return IDLE;
}