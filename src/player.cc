#include <iostream>

#include "player.h"

#include "player_input.h"
#include "components/animation_component.h"
#include "components/movement_component.h"
#include "components/hitbox_component.h"

Player::Player(
	std::shared_ptr<AnimationComponent> animationComponent,
	std::shared_ptr<MovementComponent> movementComponent,
	std::shared_ptr<HitboxComponent> hitboxComponent)
	: Entity{ animationComponent , movementComponent, hitboxComponent },
	spriteTextureSize(std::make_pair(24, 25)),
	spriteScale(3.0f)
{
	this->sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
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

	auto spriteBounds = this->sprite->getGlobalBounds();
	this->InitHitboxComponent(0, 0, spriteBounds.width, spriteBounds.height);
}

void Player::SetAnimations() const 
{
	this->animationComponent->AddAnimation(this->movementComponent->IDLE,			0.1f, 0, 2, 0, 2, spriteTextureSize.first, spriteTextureSize.second);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_UP,		0.1f, 0, 0, 2, 0, spriteTextureSize.first, spriteTextureSize.second);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_RIGHT,	0.1f, 0, 1, 2, 1, spriteTextureSize.first, spriteTextureSize.second);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_DOWN,	0.1f, 0, 2, 2, 2, spriteTextureSize.first, spriteTextureSize.second);
	this->animationComponent->AddAnimation(this->movementComponent->MOVING_LEFT,	0.1f, 0, 3, 2, 3, spriteTextureSize.first, spriteTextureSize.second);
}

void Player::Update(Input in, float dt) const
{
	const auto direction = movementComponent->Integrate(in, dt);
	animationComponent->Play(direction);

	this->hitboxComponent->Update();
}

void Player::Draw(sf::RenderTarget& target, float interp) const
{
	movementComponent->Interpolate(interp);
	target.draw(*sprite);

	this->hitboxComponent->Draw(target);
}