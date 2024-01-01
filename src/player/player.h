#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

#include "entity/entity.h"

class IRenderer;
class IPlayerMovementComponent;
class IPlayerAttributeComponent;
struct Input;

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
		std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent
    );
	~Player() override = default;
    void Update(const CollisionQuadTree& quadTree, Input& in, float dt);
	void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) const override;

protected:
	void Update(const CollisionQuadTree& quadTree, float dt) override {};
    static unsigned int CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) ;
	void InitBullets();

	std::shared_ptr<IPlayerMovementComponent> movementComponent;
	std::shared_ptr<IPlayerAttributeComponent> attributeComponent;

	std::shared_ptr<CollisionMediators> mediators;
};

#endif //PLAYER_H