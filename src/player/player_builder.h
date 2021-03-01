#ifndef PLAYER_BUILDER_H
#define PLAYER_BUILDER_H
#pragma once

#include <memory>

#include "entity/i_entity_builder.h"
#include "player.h"

class EntityObject;
class ITextureAtlas;
class IBulletSystem;
class RayCaster;

class PlayerBuilder : public IEntityObjectBuilder, public Player
{
public:
	PlayerBuilder(std::shared_ptr<ITextureAtlas> textureAtlas, std::shared_ptr<IBulletSystem> bulletSystem, sf::FloatRect bounds);
	virtual ~PlayerBuilder() = default;
	virtual EntityManifest Build() override;
private:
	void BuildShip();
	void BuildExhaust();
	void BuildTurret();
	void BuildGlowie();

	EntityManifest manifest;

	std::shared_ptr<RayCaster> rayCaster;
	std::shared_ptr<ITextureAtlas> textureAtlas;
	std::shared_ptr<IBulletSystem> bulletSystem;

	sf::FloatRect bounds;
};

#endif //PLAYER_BUILDER_H