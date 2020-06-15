#pragma once
#include <memory>

#include "../entity/i_entity_builder.h"
#include "player.h"

class EntityObject;
class MovementComponent;

class PlayerBuilder : public IEntityObjectBuilder, public Player
{
public:
	PlayerBuilder(std::shared_ptr<MovementComponent> globalMovementComponent);
	virtual ~PlayerBuilder() = default;
	virtual EntityManifest Build() const;
private:
	std::shared_ptr<EntityObject> BuildShip() const;
};