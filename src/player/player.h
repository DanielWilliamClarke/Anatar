#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

#include "entity/entity.h"

class IPlayerMovementComponent;
class IPlayerAttributeComponent;
struct Input;

class Player : public Entity
{
public:
	enum movementStates { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
	Player() = default;
	Player(
		std::shared_ptr<IEntityObjectBuilder> playerBuilder,
		std::shared_ptr<IPlayerMovementComponent> movementComponent,
		std::shared_ptr<IPlayerAttributeComponent> attributeComponent);
	virtual ~Player() = default;
	virtual void Update(std::shared_ptr<CollisionQuadTree> quadTree, Input& in, float dt);
	virtual void Draw(sf::RenderTarget& target, float interp) const override;
	virtual sf::Vector2f GetPosition() const override;
	virtual bool IsInside(sf::FloatRect& area) const override;

protected:
	virtual void Update(std::shared_ptr<CollisionQuadTree> quadTree, float dt) override {};
	const unsigned int CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const;
	void InitBullets();

	std::shared_ptr<IPlayerMovementComponent> movementComponent;
	std::shared_ptr<IPlayerAttributeComponent> attributeComponent;
};

#endif //PLAYER_H