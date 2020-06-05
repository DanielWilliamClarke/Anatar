#pragma once
#include <SFML/Graphics.hpp>


class MovementComponent
{
public:
	MovementComponent(sf::Sprite& sprite, sf::FloatRect bounds);
	virtual ~MovementComponent();

	const unsigned int Integrate(const float& dt);
	void Interpolate(const float& interp);

	enum movementStates { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

private:

	sf::Vector2f HandleInput();
	sf::Vector2f IntegrateMovement(sf::Vector2f movement, const float& dt);
	sf::Vector2f Bound(sf::Vector2f newPosition);
	const unsigned int CalculateDirection() const;

	sf::Sprite& sprite;

	// Sprite Position
	sf::Vector2f position;
	sf::Vector2f lastPosition;
	int lastDirection; 

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
};