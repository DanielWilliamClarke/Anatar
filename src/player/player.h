#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../entity/entity.h"
#include "components/movement/i_player_movement_component.h"

class Player : public Entity
{
public:
	enum movementStates { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
	Player() = default;
	Player(
		std::shared_ptr<IEntityObjectBuilder> playerBuilder,
		std::shared_ptr<IPlayerMovementComponent> movementComponent,
		std::shared_ptr<IAttributeComponent> attributeComponent);
	virtual ~Player() = default;
	virtual void Update(Input& in, float dt) const;
	virtual void Draw(sf::RenderTarget& target, float interp) const override;

protected:
	virtual void Update(float dt) const override {};
	const unsigned int CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const;

	std::shared_ptr<IPlayerMovementComponent> movementComponent;
};

#endif //PLAYER_H