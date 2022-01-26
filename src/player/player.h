#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

#include "entity/entity.h"

class IRenderer;
class IPlayerMovementComponent;
class IPlayerAttributeComponent;
struct Input;

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;

enum class PlayerObjects { SHIP, EXHAUST, TURRET, GLOWIE };

class Player : public Entity<PlayerObjects>
{
public:
	enum movementStates : int { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
	Player() = default;
	Player(
		std::unordered_map<PlayerObjects, std::shared_ptr<EntityObject>> objects,
		std::shared_ptr<IPlayerMovementComponent> movementComponent,
		std::shared_ptr<IPlayerAttributeComponent> attributeComponent,
		std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent);
	virtual ~Player() = default;
	virtual void Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, Input& in, float dt);
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const override;

protected:
	virtual void Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, float dt) override {};
	const unsigned int CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const;
	void InitBullets();

	std::shared_ptr<IPlayerMovementComponent> movementComponent;
	std::shared_ptr<IPlayerAttributeComponent> attributeComponent;

	std::shared_ptr<CollisionMediators> mediators;
};

#endif //PLAYER_H