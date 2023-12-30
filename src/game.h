#ifndef GAME_H
#define GAME_H


#include <memory>
#include <list>

#include <SFML/Graphics.hpp>
#include "game_states/game_states.h"

class Fps;
class ITextureAtlas;
class IRenderer;

template <typename T>
class State;

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

	void InitGameStates();

	void WindowEvents();
	void Update();
	void Draw();

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<IRenderer> renderer;
	std::shared_ptr<Fps> fps;
	std::shared_ptr<ITextureAtlas> textureAtlas;
	std::shared_ptr<sf::Clock> clock;

	std::shared_ptr<State<GameStates>> state;

	sf::FloatRect bounds;
	float dt;
	float accumulator;
};

#endif //GAME_H