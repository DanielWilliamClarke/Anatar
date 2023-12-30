#ifndef PLAY_STATE_BUILDER
#define PLAY_STATE_BUILDER


#include <SFML/Graphics.hpp>

#include <memory>

#include "i_play_state_builder.h"

class ITextureAtlas;

class PlayStateBuilder : public IPlayStateBuilder {
public:
	PlayStateBuilder(sf::FloatRect bounds, std::shared_ptr<ITextureAtlas> textureAtlas);
	virtual ~PlayStateBuilder() = default;

	virtual std::shared_ptr<SpaceLevel> BuildLevel() const override;
	virtual std::shared_ptr<IBulletSystem> BuildBulletSystem() const override;
	virtual std::shared_ptr<IWeaponComponent> BuildDebrisSystem(std::shared_ptr<IBulletSystem> bulletSystem) const override;
	virtual std::shared_ptr<IPlayerHud> BuildPlayerHud() const override;
	virtual std::shared_ptr<PlayerInput> BuildPlayerInput() const override;
	virtual std::shared_ptr<Player> BuildPlayer(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IWeaponComponent> debrisGenerator, std::shared_ptr<IPlayerHud> hud, float worldSpeed) const override;
	virtual std::shared_ptr<EnemySystem> BuildEnemySystem(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IWeaponComponent> debrisGenerator, float worldSpeed) const override;
	virtual std::shared_ptr<QuadTree<Collision, CollisionMediators>> BuildQuadTree() const override;
private:
	sf::FloatRect bounds;
	std::shared_ptr<ITextureAtlas> textureAtlas;
};

#endif // PLAY_STATE_BUILDER