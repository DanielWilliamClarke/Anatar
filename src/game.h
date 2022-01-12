#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

class Fps;
class TextureAtlas;
class IRenderer;
class IThreadedWorkload;

class Player;
class PlayerHud;
class PlayerInput;
class EnemySystem;
class BulletSystem;
class RandomShotWeaponComponent;
struct DamageEffects;
class SpaceLevel;

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;


class Game 
{
public:
	Game();
	virtual ~Game() = default;
	void Run();

private:
	void InitWindow();
	void InitFps();
	void InitTextureAtlas();
	void InitLevel();
	void InitPlayer();
	void InitBulletSystem();
	void InitEnemySystem();
	void WindowEvents();
	void Update();
	void Draw();

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<IRenderer> renderer;
	std::shared_ptr<IThreadedWorkload> threadableWorkload;
	std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree;

	std::shared_ptr<Fps> fps;
	std::shared_ptr<TextureAtlas> textureAtlas;
	std::shared_ptr<SpaceLevel> level;

	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerHud> playerHud;
	std::shared_ptr<PlayerInput> playerInput;

	std::shared_ptr<EnemySystem> enemySystem;
	std::shared_ptr<RandomShotWeaponComponent> debrisGenerator;

	std::shared_ptr<BulletSystem> bulletSystem;

	std::shared_ptr<sf::Clock> clock;

	sf::FloatRect bounds;

	float dt;
	float accumulator;
	float worldSpeed;
};

#endif //GAME_H