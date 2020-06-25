#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../entity/entity.h"

class Player : public Entity
{
public:
	enum movementStates { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
	Player() = default;
	Player(
		std::shared_ptr<IEntityObjectBuilder> playerBuilder,
		std::shared_ptr<IGlobalMovementComponent> movementComponent);
	virtual ~Player() = default;
	virtual void Update(Input in, float dt) const override;
	virtual void Draw(sf::RenderTarget& target, float interp) const override;

protected:
	const unsigned int CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const;
};

#endif //PLAYER_H