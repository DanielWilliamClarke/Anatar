#ifndef ENEMY_MOVEMENT_COMPONENT_H
#define ENEMY_MOVEMENT_COMPONENT_H


#include <SFML/Graphics.hpp>

#include "i_global_movement_component.h"

class EnemyMovementComponent : public IGlobalMovementComponent
{
public:

	EnemyMovementComponent(sf::FloatRect bounds, float speed, float worldSpeed);
	virtual ~EnemyMovementComponent() = default;

	virtual void SetEntityAttributes(sf::Vector2f position, sf::FloatRect entityBounds) override;
	virtual const sf::Vector2f GetPosition() const override;
	virtual const sf::Vector2f GetCenter() const override;
	virtual const sf::FloatRect GetBounds() const override;

	virtual sf::Vector2f Integrate(const float& dt) override;
	virtual sf::Vector2f Interpolate(const float& interp) override;

private:

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
	float worldSpeed;
	sf::FloatRect bounds;
};

#endif //ENEMY_MOVEMENT_COMPONENT_H