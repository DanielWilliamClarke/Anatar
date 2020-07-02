#ifndef PLAYER_BUILDER_H
#define PLAYER_BUILDER_H
#pragma once

#include <memory>

#include "../entity/i_entity_builder.h"
#include "player.h"

class EntityObject;
class ITextureAtlas;
class IBulletSystem;

class PlayerBuilder : public IEntityObjectBuilder, public Player
{
public:
	PlayerBuilder(std::shared_ptr<ITextureAtlas> textureAtlas, std::shared_ptr<IBulletSystem> bulletSystem);
	virtual ~PlayerBuilder() = default;
	virtual EntityManifest Build() override;
private:
	void BuildShip();
	void BuildExhaust();
	void BuildTurret();

	EntityManifest manifest;

	std::shared_ptr<ITextureAtlas> textureAtlas;
	std::shared_ptr<IBulletSystem> bulletSystem;
};

#endif //PLAYER_BUILDER_H