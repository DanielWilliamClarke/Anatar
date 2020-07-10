#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

class Fps;
class TextureAtlas;
class GlowShaderRenderer;

class SpaceLevel;
class Entity;
class Player;
class PlayerHud;
class PlayerInput;
class EnemySystem;
class BulletSystem;
struct BulletConfig;
class RandomShotWeaponComponent;

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

	std::shared_ptr<Fps> fps;
	std::shared_ptr<TextureAtlas> textureAtlas;
	std::shared_ptr<SpaceLevel> level;

	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerHud> playerHud;
	std::shared_ptr<PlayerInput> playerInput;
	std::shared_ptr<BulletSystem> playerBulletSystem;
	std::list<std::shared_ptr<Entity>> playerTargets;

	std::shared_ptr<EnemySystem> enemySystem;
	std::shared_ptr<BulletSystem> enemyBulletSystem;

	std::shared_ptr<BulletSystem> debrisSystem;
	std::shared_ptr<BulletConfig> debrisConfig;
	std::shared_ptr<RandomShotWeaponComponent> debrisGenerator;

	std::shared_ptr<sf::Clock> clock;

	sf::FloatRect bounds;

	float dt;
	float accumulator;
	float worldSpeed;
};

#endif //GAME_H