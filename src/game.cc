#include <SFML/Graphics.hpp>

#include <chrono>

#include "game.h"
#include "util/fps.h"
#include "util/texture_atlas.h"

#include "entity/Entity.h"
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

#include "bullet/bullet_system.h"
#include "components/weapon/burst/burst_shot_weapon_component_factory.h"
#include "components/weapon/single/single_shot_weapon_component_factory.h"

#include "components/animation/animation_component.h"
#include "components/hitbox/hitbox_component.h"

static const std::string shaderCode = \
"uniform vec2 frag_LightOrigin;"\
"uniform vec3 frag_LightColor;"\
"uniform float frag_LightAttenuation;"\
"uniform vec2 frag_ScreenResolution;"\
"void main(){"\
" vec2 baseDistance =  gl_FragCoord.xy;"\
" baseDistance.y = frag_ScreenResolution.y-baseDistance.y;"\
" vec2 distance=frag_LightOrigin - baseDistance;"\
" float linear_distance = length(distance);"\
" float attenuation=1.0/( frag_LightAttenuation*linear_distance + frag_LightAttenuation*linear_distance);"\
" vec4 lightColor = vec4(frag_LightColor,  clamp(frag_LightAttenuation, 0.0 ,frag_LightAttenuation));"\
" vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor; gl_FragColor=color;}";

Game::Game()
    : clock(std::make_shared<sf::Clock>()),
    dt(1.0f / 60.0f),
    accumulator(0.0f),
    worldSpeed(40.0f)
{
    this->InitWindow();
    this->InitFps();
    this->InitTextureAtlas();
    this->InitLevel();
    this->InitBulletSystem();
    this->InitPlayer();
    this->InitEnemySystem();
}

void Game::InitWindow()
{
    this->window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(1280, 720),
        "Space Shooter",
        sf::Style::Titlebar | sf::Style::Close);

    this->windowTexture = std::make_shared<sf::RenderTexture>();
    this->windowTexture->create(1280, 720);

    auto view = this->window->getView();
    sf::Vector2f viewCenter(view.getCenter());
    sf::Vector2f viewSize(view.getSize());
    bounds = sf::FloatRect(viewCenter.x - viewSize.x / 2, // left
        viewCenter.y - viewSize.y / 2, // top
        viewSize.x,
        viewSize.y);

    this->glowSprite = std::make_shared<sf::Sprite>();
    this->glowSprite->setTexture(this->windowTexture->getTexture());
    this->glowSprite->setOrigin(this->glowSprite->getTextureRect().width / 2, this->glowSprite->getTextureRect().height / 2);
    this->glowSprite->setPosition(viewSize.x / 2.f, viewSize.y / 2.f);

    this->shader.loadFromMemory(shaderCode, sf::Shader::Fragment);
    this->shader.setUniform("frag_ScreenResolution", sf::Vector2f(viewSize.x, viewSize.y));
}

void Game::InitFps()
{
    this->fps = std::make_shared<Fps>();
}

void Game::InitTextureAtlas()
{
    this->textureAtlas = std::make_shared<TextureAtlas>();

    this->textureAtlas
        ->AddTexture("playerShip", "assets/viperFrames.png")
        ->AddTexture("playerExhaust", "assets/viperExhaust.png")
        ->AddTexture("playerTurret", "assets/viperTurret.png")
        ->AddTexture("enemy1", "assets/enemy_1.png")
        ->AddTexture("enemy2", "assets/enemy_2.png")
        ->AddTexture("enemy3", "assets/enemy_3.png")
        ->AddTexture("boss1", "assets/boss_1.png");
}

void Game::InitLevel()
{
    auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
    auto randGenerator = std::make_shared<RandomNumberMersenneSource<int>>(seed);
    this->level = std::make_shared<SpaceLevel>(randGenerator, this->window->getView().getSize());
}

void Game::InitBulletSystem()
{
    this->enemyBulletSystem = std::make_shared<BulletSystem>(shader, bounds, BulletSystem::LEFT);
    this->playerBulletSystem = std::make_shared<BulletSystem>(shader, bounds, BulletSystem::RIGHT);
}


void Game::InitPlayer() 
{
    auto playerBuilder = std::make_shared<PlayerBuilder>(this->textureAtlas,  this->playerBulletSystem);
    auto movementComponent = std::make_shared<PlayerMovementComponent>(bounds, worldSpeed);
    this->player = std::make_shared<Player>(playerBuilder, movementComponent);
    this->playerInput = std::make_shared<PlayerInput>();
}

void Game::InitEnemySystem()
{
    this->enemySystem = std::make_shared<EnemySystem>();

    this->enemySystem

        ->AddFactory(1.0f, std::make_shared<EnemyTypeFactory>(
            EnemyConfig(EnemyTypeFactory::BuildOribitalEnemy,
                EnemyMotionConfig(bounds, worldSpeed, 200.0f),
                EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy1"), 6, 0.1f, 1.0f),
                EnemyWeaponConfig(std::make_shared<SingleShotWeaponComponentFactory>(), this->enemyBulletSystem, 1.0f))))

        ->AddFactory(3.0f, std::make_shared<EnemyTypeFactory>(
            EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
                EnemyMotionConfig(bounds, worldSpeed, 300.0f),
                EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy2"), 14, 0.1f, 1.0f),
                EnemyWeaponConfig(std::make_shared<SingleShotWeaponComponentFactory>(), this->enemyBulletSystem, 2.0f))))

        ->AddFactory(6.0f, std::make_shared<EnemyTypeFactory>(
            EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
                EnemyMotionConfig(bounds, worldSpeed, 75.0f),
                EnemyAnimationConfig(this->textureAtlas->GetTexture("enemy3"), 9, 0.1f, 1.0f),
                EnemyWeaponConfig(std::make_shared<BurstShotWeaponComponentFactory>(90.0f, 10.0f), this->enemyBulletSystem, 3.0f))))

        ->AddFactory(50.0f, std::make_shared<EnemyTypeFactory>(
            EnemyConfig(EnemyTypeFactory::BuildLinearEnemy,
                EnemyMotionConfig(bounds, worldSpeed, 75.0f),
                EnemyAnimationConfig(this->textureAtlas->GetTexture("boss1"), 12, 0.5f, 2.0f),
                EnemyWeaponConfig(std::make_shared<BurstShotWeaponComponentFactory>(180.0f, 100.0f), this->enemyBulletSystem, 10.0f))));
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
        this->enemyBulletSystem->Update(dt, worldSpeed, { this->player });
        this->playerBulletSystem->Update(dt, worldSpeed, this->enemySystem->GetEnemies());
        this->fps->Update();
        this->accumulator -= this->dt;
    }
}

void Game::Draw() 
{
    auto interp = this->accumulator / this->dt;
    this->window->clear(sf::Color::Black);
    this->windowTexture->clear(sf::Color::Transparent);

    //Draw stuff that glows
    this->level->Draw(*this->windowTexture, *this->glowSprite, this->shader);
    this->enemyBulletSystem->Draw(*this->windowTexture, *this->glowSprite, interp);
    this->playerBulletSystem->Draw(*this->windowTexture, *this->glowSprite, interp);
    this->windowTexture->display();
    this->window->draw(*this->glowSprite);

    // Draw everything else
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
