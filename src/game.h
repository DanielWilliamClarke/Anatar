#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class Fps;
class TextureAtlas;
class SpaceLevel;
class Player;
class PlayerInput;
class EnemySystem;
class BulletSystem;

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
	std::shared_ptr<Fps> fps;
	std::shared_ptr<TextureAtlas> textureAtlas;
	std::shared_ptr<SpaceLevel> level;
	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerInput> playerInput;
	std::shared_ptr<EnemySystem> enemySystem;
	std::shared_ptr<BulletSystem> enemyBulletSystem;
	std::shared_ptr<BulletSystem> playerBulletSystem;
	std::shared_ptr<sf::Clock> clock;

	sf::FloatRect bounds;

	float dt;
	float accumulator;
	float worldSpeed;
};

#endif //GAME_H