#pragma once
#include <SFML/Graphics.hpp>

struct Input;

class MovementComponent
{
public:

	MovementComponent(sf::FloatRect bounds);
	virtual ~MovementComponent() = default;

	void SetEntityAttributes(sf::Vector2f position, sf::FloatRect entityBounds);
	const sf::Vector2f GetPosition() const;
	const sf::Vector2f GetCenter() const;

	sf::Vector2f Integrate(Input in, const float& dt);
	sf::Vector2f Interpolate(const float& interp);

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