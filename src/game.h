#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>

namespace sf {
	class RenderWindow;
	class Clock;
}

class Fps;
class SpaceLevel;
class Player;
class PlayerInput;

class Game 
{
public:
	Game();
	virtual ~Game() = default;
	void Run();

private:

	void InitWindow();
	void InitFps();
	void InitLevel();
	void InitPlayer();

	void WindowEvents();
	void Update();
	void Draw();

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Fps> fps;
	std::shared_ptr<SpaceLevel> level;
	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerInput> playerInput;
	std::shared_ptr<sf::Clock> clock;

	float dt;
	float accumulator;
	float worldSpeed;
};

#endif //GAME_H