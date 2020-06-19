#include <SFML/Graphics.hpp>

#include "game.h"
#include "fps.h"

#include "player/player_builder.h"
#include "player/player.h"
#include "player/player_input.h"

#include "components/movement/global_movement_component.h"

#include "components/animation/animation_component_factory.h"
#include "components/animation/animation_component.h"

#include "components/hitbox/hitbox_component_factory.h"
#include "components/hitbox/hitbox_component.h"

Game::Game() 
    : clock(std::make_shared<sf::Clock>()),
    dt(1.0f / 60.0f),
    accumulator(0.0f)
{
    this->InitWindow();
    this->InitFps();
    this->InitPlayer();
}

void Game::InitWindow()
{
	this->window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(800, 600),
		"Space Shooter",
		sf::Style::Titlebar | sf::Style::Close);
}

void Game::InitPlayer() 
{
    auto view = this->window->getView();
    sf::Vector2f viewCenter(view.getCenter());
    sf::Vector2f viewSize(view.getSize());
    sf::FloatRect bounds(viewCenter.x - viewSize.x / 2, // left
        viewCenter.y - viewSize.y / 2, // top
        viewSize.x,
        viewSize.y);

    auto playerBuilder = std::make_shared<PlayerBuilder>();
    auto movementComponent = std::make_shared<GlobalMovementComponent>(bounds);
    this->player = std::make_shared<Player>(playerBuilder, movementComponent);
    this->playerInput = std::make_shared<PlayerInput>();
}

void Game::InitFps() 
{
    this->fps = std::make_shared<Fps>();
}

void Game::WindowEvents()
{
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }           
}

void Game::Update() 
{
    auto in = this->playerInput->SampleInput();

    this->accumulator += this->clock->restart().asSeconds();
    while (this->accumulator >= this->dt)
    {
        this->player->Update(in, this->dt);
        this->fps->Update();
        this->accumulator -= this->dt;
    }
}

void Game::Draw() 
{
    auto interp = this->accumulator / this->dt;
    this->window->clear(sf::Color(255, 255, 255, 255));
    this->player->Draw(*this->window, interp);
    this->fps->Draw(*this->window);
    this->window->display();
}

void Game::Run() 
{
    while (this->window->isOpen())
    {
        this->WindowEvents();
        this->Update();
        this->Draw();
    }
}
