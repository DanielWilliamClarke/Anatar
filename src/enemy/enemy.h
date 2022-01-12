#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "entity/entity.h"

class IRenderer;

struct Collision;
struct CollisionMediators;
template<typename C, typename P>
class QuadTree;

enum EnemyObjects : ObjectID { ENEMY };

class Enemy : public Entity
{
public:
	enum movementStates { IDLE = 0 };
	Enemy() = default;
	Enemy(
		EntityManifest manifest,
		std::shared_ptr<IGlobalMovementComponent> movementComponent,
		std::shared_ptr<IAttributeComponent> attributeComponent,
		std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent,
		sf::Vector2f initialPosition);
	virtual ~Enemy() = default;
	virtual void Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, float dt) override;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const override;
	virtual sf::Vector2f GetPosition() const override;

private:
	void InitBullets();
};

#endif //ENEMY_H