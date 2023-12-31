#ifndef PLAY_STATE
#define PLAY_STATE


#include "game_states/game_states.h"
#include "state/state.h"

class IPlayStateBuilder;

class SpaceLevel;
class IBulletSystem;
class IWeaponComponent;

class IPlayerHud;
class Player;
class PlayerInput;

class EnemySystem;

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;

class PlayState : public State<GameStates> {
public:
	explicit PlayState(std::shared_ptr<IPlayStateBuilder> builder);
	~PlayState() override = default;

	void Update(float dt) override;
    void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) const override;

protected: 
	void Setup() override;
	void TearDown() override;

private: 
	std::shared_ptr<IPlayStateBuilder> builder;

	std::shared_ptr<SpaceLevel> level;
	std::shared_ptr<IBulletSystem> bulletSystem;
	std::shared_ptr<IPlayerHud> hud;
	std::shared_ptr<PlayerInput> input;

	std::shared_ptr<Player> player;
	std::shared_ptr<EnemySystem> enemySystem;

	std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree;
	std::shared_ptr<IWeaponComponent> debrisEmitter;

	float worldSpeed;
};

#endif