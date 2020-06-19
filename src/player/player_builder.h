#pragma once
#include <memory>

#include "../entity/i_entity_builder.h"
#include "player.h"

class EntityObject;

class PlayerBuilder : public IEntityObjectBuilder, public Player
{
public:
	PlayerBuilder() = default;
	virtual ~PlayerBuilder() = default;
	virtual EntityManifest Build() const;
private:
	std::shared_ptr<EntityObject> BuildShip() const;
	std::shared_ptr<EntityObject> BuildExhaust() const;
};