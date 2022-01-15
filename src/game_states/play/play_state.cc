#include "play_state.h"

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
	this->level = builder->BuildLevel();
	this->bulletSystem = builder->BuildBulletSystem();
	this->input = builder->BuildPlayerInput();
	this->hud = builder->BuildPlayerHud();

	auto debrisSystem = builder->BuildDebrisSystem(bulletSystem);
	this->player = builder->BuildPlayer(bulletSystem, debrisSystem, hud, worldSpeed);
	this->enemySystem = builder->BuildEnemySystem(bulletSystem, debrisSystem, worldSpeed);
}

std::shared_ptr<State<GameStates>> PlayState::Update(float dt)
{
	auto in = this->input->SampleInput();
	this->quadTree = builder->BuildQuadTree();

	this->level->Update(worldSpeed, dt);
	this->player->Update(this->quadTree, in, dt);
	this->enemySystem->Update(this->quadTree, dt);
	this->bulletSystem->Update(this->quadTree, dt, worldSpeed);

	if (this->player->HasDied())
	{
		exit(0); // Here we would transition to dead screen etc
	}

	return this->shared_from_this();
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