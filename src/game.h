#ifndef GAME_H
#define GAME_H
#pragma once

#include <memory>

namespace sf {
	class RenderWindow;
	class Clock;
}

class Fps;
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
	void InitPlayer();

	void WindowEvents();
	void Update();
	void Draw();

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Fps> fps;
	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerInput> playerInput;
	std::shared_ptr<sf::Clock> clock;

	float dt;
	float accumulator;
};

#endif //GAME_H