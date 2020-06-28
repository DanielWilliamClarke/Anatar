#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../entity/entity.h"

class Enemy : public Entity
{
public:
	enum movementStates { IDLE = 0 };
	Enemy() = default;
	Enemy(
		std::shared_ptr<IEntityObjectBuilder> playerBuilder,
		std::shared_ptr<IGlobalMovementComponent> movementComponent);

	virtual ~Enemy() = default;

	virtual void Update(float dt) const override;
	virtual void Draw(sf::RenderTarget& target, float interp) const override;

private: 

};


#endif //ENEMY_H