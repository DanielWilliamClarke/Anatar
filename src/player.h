#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "entity/entity.h"

class Player : public Entity
{
public:
	enum movementStates { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

	Player(
		std::shared_ptr<EntityComposition> group,
		std::shared_ptr<MovementComponent> movementComponent);
	virtual ~Player() = default;
	virtual void Update(Input in, float dt) const;
	virtual void Draw(sf::RenderTarget& target, float interp) const;

private:
	virtual void Update(float dt) const {};
	void InitShip() const;
	const unsigned int CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const;

	std::pair<int, int> spriteTextureSize;
	float spriteScale;	
};
