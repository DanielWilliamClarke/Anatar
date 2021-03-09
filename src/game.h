#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

#include "quad_tree/quad_tree.h"

class Fps;
class TextureAtlas;
class GlowShaderRenderer;
class IThreadedWorkload;

class SpaceLevel;
class Entity;
struct EntityCollision;
class Player;
class PlayerHud;
class PlayerInput;
class EnemySystem;
class BulletSystem;
class RandomShotWeaponComponent;
struct DamageEffects;

typedef QuadTree<Entity, EntityCollision> CollisionQuadTree;

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
	std::shared_ptr<GlowShaderRenderer> glowRenderer;
	std::shared_ptr<IThreadedWorkload> threadableWorkload;
	std::shared_ptr<CollisionQuadTree> quadTree;

	std::shared_ptr<Fps> fps;
	std::shared_ptr<TextureAtlas> textureAtlas;
	std::shared_ptr<SpaceLevel> level;

	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerHud> playerHud;
	std::shared_ptr<PlayerInput> playerInput;
	std::vector<std::shared_ptr<Entity>> playerTargets;

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