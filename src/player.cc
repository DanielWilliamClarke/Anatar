#include <iostream>
#include "animation_component.h"
#include "movement_component.h"
#include "player.h"

Player::Player(
	sf::Sprite& sprite,
	std::shared_ptr<AnimationComponent> animationComponent, 
	std::shared_ptr<MovementComponent> movementComponent) :
	sprite(sprite),
	animationComponent(animationComponent),
	movementComponent(movementComponent)
{
  animationComponent->AddAnimation(movementComponent->MOVING_UP,    0.1, 0, 0, 2, 0, 24, 25);
  animationComponent->AddAnimation(movementComponent->MOVING_RIGHT, 0.1, 0, 1, 2, 1, 24, 25);
  animationComponent->AddAnimation(movementComponent->MOVING_DOWN,  0.1, 0, 2, 2, 2, 24, 25);
  animationComponent->AddAnimation(movementComponent->MOVING_LEFT,  0.1, 0, 3, 2, 3, 24, 25);
}

void Player::Update(float dt)
{
	const auto direction = movementComponent->Integrate(dt);
	animationComponent->Play(direction);
}

void Player::Draw(sf::RenderWindow &window, float interp)
{
	movementComponent->Interpolate(interp);
	window.draw(sprite);  
}