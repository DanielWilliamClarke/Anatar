#include "play_state.h"

#include <iostream>

#include "i_play_state_builder.h"
#include "renderer/i_renderer.h"

#include "level/space_level.h"

#include "bullet/i_bullet_system.h"

#include "player/player_input.h"
#include "ui/player_hud.h"

#include "player/player.h"
#include "enemy/enemy_system.h"

PlayState::PlayState(std::shared_ptr<IPlayStateBuilder> builder)
	: builder(builder), worldSpeed(40.f)
{
	this->Setup();
}

void PlayState::Setup()
{
	std::cout << "play setting up" << std::endl;
	this->quadTree = builder->BuildQuadTree();

	this->level = builder->BuildLevel();
	this->bulletSystem = builder->BuildBulletSystem();
	this->input = builder->BuildPlayerInput();
	this->hud = builder->BuildPlayerHud();

	this->debrisEmitter = builder->BuildDebrisSystem(bulletSystem);
	this->player = builder->BuildPlayer(bulletSystem, debrisEmitter, hud, worldSpeed);
	this->enemySystem = builder->BuildEnemySystem(bulletSystem, debrisEmitter, worldSpeed);
}

void PlayState::TearDown()
{
	std::cout << "play tearing down" << std::endl;
}

void PlayState::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->Forward(GameStates::MENU);
		return;
	}

	auto in = this->input->SampleInput();
	this->quadTree = builder->BuildQuadTree();

	this->level->Update(worldSpeed, dt);
	this->player->Update(this->quadTree, in, dt);
	this->enemySystem->Update(this->quadTree, dt);
	this->bulletSystem->Update(this->quadTree, dt, worldSpeed);

	if (this->player->HasDied())
	{
		this->Back();
	}
}

void PlayState::Draw(std::shared_ptr<IRenderer> renderer, float interp) const
{
	this->level->Draw(renderer);
	this->bulletSystem->Draw(renderer, interp);
	this->player->Draw(renderer, interp);
	this->enemySystem->Draw(renderer, interp);
	this->hud->Draw(renderer);
	this->quadTree->Draw(renderer);
}

