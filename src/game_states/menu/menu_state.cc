#include "menu_state.h"


#include <iostream>

#include "renderer/i_renderer.h"

MenuState::MenuState() {
	font.loadFromFile("./assets/EightBitDragon-anqx.ttf");
	text.setFont(font);
	text.setScale(2, 2);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(50.0f, 50.0f);
	text.setString("PRESS SPACE TO START");
}

void MenuState::Setup()
{
	std::cout << "menu setting up" << std::endl;
}

void MenuState::TearDown()
{
	std::cout << "menu tearing down" << std::endl;
}

void MenuState::Update(float dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return this->Forward(GameStates::PLAY);
	}
}

void MenuState::Draw(std::shared_ptr<IRenderer> renderer, float interp) const
{
	renderer->GetTarget().draw(text);
}
