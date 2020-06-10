#include <iostream>

#include "player.h"

#include "player_input.h"
#include "animation_component.h"
#include "movement_component.h"

Player::Player(
	std::shared_ptr<AnimationComponent> animationComponent,
	std::shared_ptr<MovementComponent> movementComponent)
	: Entity{ animationComponent , movementComponent }
{
	this->sprite->setScale(sf::Vector2f(3.0f, 3.0f));
	this->texture = std::make_shared<sf::Texture>();
	this->texture->loadFromFile("./assets/pikaFrames.png");

	this->InitPlayer();
}

void Player::InitPlayer() const 
{
	this->SetTexture(this->texture);
	this->InitAnimationComponent(this->texture);
	this->InitMovementComponent();
	this->SetAnimations();
}

void Player::SetAnimations() const 
{
	this->animationComponent->AddAnimation(this->movementComponent->IDLE, 0.1f, 0, 2, 0, 2, 24, 25);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_UP, 0.1f, 0, 0, 2, 0, 24, 25);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_RIGHT, 0.1f, 0, 1, 2, 1, 24, 25);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_DOWN, 0.1f, 0, 2, 2, 2, 24, 25);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_LEFT, 0.1f, 0, 3, 2, 3, 24, 25);
}

void Player::Update(Input in, float dt) const
{
	const auto direction = movementComponent->Integrate(in, dt);
	animationComponent->Play(direction);
}

void Player::Draw(sf::RenderTarget& target, float interp) const
{
	movementComponent->Interpolate(interp);
	target.draw(*sprite);
}