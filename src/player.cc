#include <iostream>

#include "player.h"

#include "player_input.h"
#include "animation_component.h"
#include "movement_component.h"

Player::Player(
	std::shared_ptr<AnimationComponent> animationComponent,
	std::shared_ptr<MovementComponent> movementComponent)
	: animationComponent(animationComponent),
	movementComponent(movementComponent)
{
	sprite = std::make_shared<sf::Sprite>();
	sprite->setScale(sf::Vector2f(3.0f, 3.0f));
	this->movementComponent->SetSprite(sprite);

	this->texture = std::make_shared<sf::Texture>();
	this->texture->loadFromFile("./assets/pikaFrames.png");
	this->animationComponent->SetAssets(sprite, texture);

	this->animationComponent->AddAnimation(movementComponent->IDLE, 0.1f, 0, 2, 0, 2, 24, 25);
	this->animationComponent->AddAnimation(movementComponent->MOVING_UP, 0.1f, 0, 0, 2, 0, 24, 25);
	this->animationComponent->AddAnimation(movementComponent->MOVING_RIGHT, 0.1f, 0, 1, 2, 1, 24, 25);
	this->animationComponent->AddAnimation(movementComponent->MOVING_DOWN, 0.1f, 0, 2, 2, 2, 24, 25);
	this->animationComponent->AddAnimation(movementComponent->MOVING_LEFT, 0.1f, 0, 3, 2, 3, 24, 25);
}

void Player::Update(Input in, float dt) const
{
	const auto direction = movementComponent->Integrate(in, dt);
	animationComponent->Play(direction);
}

void Player::Draw(sf::RenderWindow& window, float interp) const
{
	movementComponent->Interpolate(interp);
	window.draw(*sprite);
}