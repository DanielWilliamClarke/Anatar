#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H


#include <SFML/Graphics.hpp>

#include "i_player_movement_component.h"

struct Input;

class PlayerMovementComponent: public IPlayerMovementComponent
{
public:

	PlayerMovementComponent(sf::FloatRect bounds, float& worldSpeed);
	virtual ~PlayerMovementComponent() = default;

	virtual void SetEntityAttributes(sf::Vector2f position, sf::FloatRect entityBounds) override;
	virtual const sf::Vector2f GetPosition() const override;
	virtual const sf::Vector2f GetCenter() const override;
	virtual const sf::FloatRect GetBounds() const override;

	virtual sf::Vector2f Integrate(Input& in, const float& dt) override;
	virtual sf::Vector2f Interpolate(const float& interp) override;

protected:
	virtual sf::Vector2f Integrate(const float& dt) override { return { 0,0 }; };

private:
	
	sf::Vector2f Bound(sf::Vector2f newPosition);

	// Sprite Position
	sf::Vector2f position;
	sf::Vector2f lastPosition;

	// Physics
	sf::Vector2f gravity;
	sf::Vector2f maxThrust;
	sf::Vector2f thrust;	
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f worldVelocity;

	float force;
	float mass;
	float movementSpeed;
	float& worldSpeed;

	// Bounds checking
	sf::FloatRect bounds;
	sf::FloatRect entityBounds;

};

#endif //PLAYER_MOVEMENT_COMPONENT_H