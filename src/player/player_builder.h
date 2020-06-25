#ifndef PLAYER_BUILDER_H
#define PLAYER_BUILDER_H
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
	virtual EntityManifest Build() override;
private:
	void BuildShip();
	void BuildExhaust();
	void BuildTurret();

	EntityManifest manifest;
};

#endif //PLAYER_BUILDER_H