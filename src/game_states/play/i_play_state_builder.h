#ifndef I_PLAY_STATE_BUILDER
#define I_PLAY_STATE_BUILDER

#include "quad_tree/collision_quad_tree.h"

class ITextureAtlas;
class SpaceLevel;
class IBulletSystem;
class IWeaponComponent;

class IPlayerHud;
class Player;
class PlayerInput;

class EnemySystem;

class IPlayStateBuilder {
public:
	IPlayStateBuilder() = default;
	virtual ~IPlayStateBuilder() = default;

	[[nodiscard]] virtual std::shared_ptr<SpaceLevel> BuildLevel() const = 0;
    [[nodiscard]] virtual std::shared_ptr<IBulletSystem> BuildBulletSystem() const = 0;
    [[nodiscard]] virtual std::shared_ptr<IWeaponComponent> BuildDebrisSystem(std::shared_ptr<IBulletSystem> bulletSystem) const = 0;
    [[nodiscard]] virtual std::shared_ptr<IPlayerHud> BuildPlayerHud() const = 0;
    [[nodiscard]] virtual std::shared_ptr<PlayerInput> BuildPlayerInput() const = 0;
    [[nodiscard]] virtual std::shared_ptr<Player> BuildPlayer(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IWeaponComponent> debrisGenerator, std::shared_ptr<IPlayerHud> hud, float worldSpeed) const = 0;
    [[nodiscard]] virtual std::shared_ptr<EnemySystem> BuildEnemySystem(std::shared_ptr<IBulletSystem> bulletSystem, std::shared_ptr<IWeaponComponent> debrisGenerator, float worldSpeed) const = 0;
    [[nodiscard]] virtual CollisionQuadTree BuildQuadTree() const = 0;
};

#endif // I_PLAY_STATE_BUILDER