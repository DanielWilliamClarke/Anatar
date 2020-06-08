#pragma once
#include <SFML/Graphics.hpp>

struct Input;

class MovementComponent
{
public:
	MovementComponent(sf::FloatRect bounds);
	virtual ~MovementComponent();

	void SetSprite(std::shared_ptr<sf::Sprite> sprite);
	const unsigned int Integrate(Input in, const float& dt);
	void Interpolate(const float& interp);

	enum movementStates { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

private:

	sf::Vector2f GetCenter() const;
	sf::Vector2f IntegrateMovement(Input in, const float& dt);
	sf::Vector2f Bound(sf::Vector2f newPosition);
	const unsigned int CalculateDirection() const;

	std::shared_ptr<sf::Sprite> sprite;

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
};