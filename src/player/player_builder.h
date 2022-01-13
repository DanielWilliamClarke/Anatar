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

class PlayerBuilder : public IEntityObjectBuilder<PlayerObjects>, public Player
{
public:
	PlayerBuilder(std::shared_ptr<ITextureAtlas> textureAtlas, std::shared_ptr<IBulletSystem> bulletSystem, sf::FloatRect bounds);
	virtual ~PlayerBuilder() = default;
	virtual EntityManifest<PlayerObjects> Build() override;
private:
	std::shared_ptr<EntityObject> BuildShip(std::shared_ptr<sf::Sprite> ship);
	std::shared_ptr<EntityObject> BuildExhaust(std::shared_ptr<sf::Sprite> ship);
	std::shared_ptr<EntityObject> BuildTurret(std::shared_ptr<sf::Sprite> ship);
	std::shared_ptr<EntityObject> BuildGlowie(std::shared_ptr<sf::Sprite> ship);

	std::shared_ptr<RayCaster> rayCaster;
	std::shared_ptr<ITextureAtlas> textureAtlas;
	std::shared_ptr<IBulletSystem> bulletSystem;

	sf::FloatRect bounds;
};

#endif //PLAYER_BUILDER_H