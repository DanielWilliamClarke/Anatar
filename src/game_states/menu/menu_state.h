#ifndef MENU_STATE
#define MENU_STATE

#include <SFML/Graphics.hpp>

#include "game_states/game_states.h"
#include "state/state.h"

class MenuState : public State<GameStates> {
public:
	MenuState();
	~MenuState() override = default;

	void Update(float dt) override;
	void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) const override;

protected:
	void Setup() override;
	void TearDown() override;

private:
	sf::Font font;
	sf::Text text;
};

#endif