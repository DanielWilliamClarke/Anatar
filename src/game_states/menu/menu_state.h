#ifndef MENU_STATE
#define MENU_STATE
#pragma once

#include <SFML/Graphics.hpp>

#include "game_states/game_states.h"
#include "state/state.h"

class MenuState : public State<GameStates> {
public:
	MenuState();
	virtual ~MenuState() = default;

	virtual void Update(float dt) override;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const override;

protected:
	virtual void Setup() override;
	virtual void TearDown() override;

private:
	sf::Font font;
	sf::Text text;
};

#endif // MENU_STATE