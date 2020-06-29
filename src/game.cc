#include <SFML/Graphics.hpp>

#include <chrono>

#include "game.h"
#include "fps.h"

#include "player/player_builder.h"
#include "player/player.h"
#include "player/player_input.h"

#include "enemy/enemy_system.h"
#include "enemy/enemy_type_factory.h"

#include "util/random_number_mersenne_source.cc"
#include "level/space_level.h"

#include "components/movement/enemy_movement_component.h"
#include "components/movement/player_movement_component.h"
#include "components/movement/offset_movement_component.h"

#include "components/animation/animation_component.h"
#include "components/hitbox/hitbox_component.h"

Game::Game()
    : clock(std::make_shared<sf::Clock>()),
    dt(1.0f / 60.0f),
    accumulator(0.0f),
    worldSpeed(40.0f)
{
    this->InitWindow();
    this->InitFps();
    this->InitLevel();
    this->InitPlayer();
    this->InitEnemySystem();
}

void Game::InitWindow()
{
	this->window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(1280, 720),
		"Space Shooter",
		sf::Style::Titlebar | sf::Style::Close);

    auto view = this->window->getView();
    sf::Vector2f viewCenter(view.getCenter());
    sf::Vector2f viewSize(view.getSize());
    bounds = sf::FloatRect(viewCenter.x - viewSize.x / 2, // left
        viewCenter.y - viewSize.y / 2, // top
        viewSize.x,
        viewSize.y);
}

void Game::InitLevel()
{
    auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
    auto randGenerator = std::make_shared<RandomNumberMersenneSource<int>>(seed);
    this->level = std::make_shared<SpaceLevel>(randGenerator, this->window->getView().getSize());
}

void Game::InitPlayer() 
{
    auto playerBuilder = std::make_shared<PlayerBuilder>();
    auto movementComponent = std::make_shared<PlayerMovementComponent>(bounds, worldSpeed);
    this->player = std::make_shared<Player>(playerBuilder, movementComponent);
    this->playerInput = std::make_shared<PlayerInput>();
}

void Game::InitEnemySystem()
{
    this->enemySystem = std::make_shared<EnemySystem>();

    this->enemySystem
        ->AddFactory(10.0f, std::make_shared<EnemyTypeFactory>(
            EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
                EnemyMotionConfig(bounds, worldSpeed, 100.0f),
                EnemyAnimationConfig("assets/enemy_3.png", 9, 0.2f, 1.0f))))
        ->AddFactory(5.0f, std::make_shared<EnemyTypeFactory>(
            EnemyConfig(EnemyTypeFactory::BuildOribitalEnemy,
                EnemyMotionConfig(bounds, worldSpeed, 100.0f),
                EnemyAnimationConfig("assets/enemy_1.png", 6, 0.2f, 1.0f))));
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
        this->level->Update(worldSpeed, dt);
        this->player->Update(in, this->dt);
        this->enemySystem->Update(dt);
        this->fps->Update();
        this->accumulator -= this->dt;
    }
}

void Game::Draw() 
{
    auto interp = this->accumulator / this->dt;
    this->window->clear(sf::Color::Black);
    this->level->Draw(*this->window);
    this->player->Draw(*this->window, interp);
    this->enemySystem->Draw(*this->window, interp);
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
