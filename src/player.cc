#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

#include "player.h"

#include "entity/entity_composition.h"
#include "entity/entity_object.h"
#include "entity/entity_update.h"

#include "player_input.h"
#include "components/animation_component.h"
#include "components/movement_component.h"
#include "components/hitbox_component.h"

Player::Player(
	std::shared_ptr<EntityComposition> group,
	std::shared_ptr<MovementComponent> globalMovementComponent)
	: Entity{ group , globalMovementComponent },
	spriteTextureSize(std::make_pair(33, 26)),
	spriteScale(2.0f)
{
	this->InitShip();
}

void Player::InitShip() const
{
	const auto ship = this->group->AddAttachment("ship");

	auto sprite = ship->GetSprite();

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("./assets/viperFrames.png");
	ship->SetTexture(texture);
	ship->InitAnimationComponent(texture);

	sprite->setPosition(this->globalMovementComponent->GetCenter());
	this->globalMovementComponent->SetEntityAttributes(sprite->getPosition(), sprite->getGlobalBounds());
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	ship->AddAnimation(this->IDLE, 0.2f, 0, 0, 0, 0, spriteTextureSize.first, spriteTextureSize.second);
	ship->AddAnimation(this->MOVING_UP, 0.2f, 0, 1, 2, 1, spriteTextureSize.first, spriteTextureSize.second);
	ship->AddAnimation(this->MOVING_DOWN, 0.2f, 0, 0, 2, 0, spriteTextureSize.first, spriteTextureSize.second);

	auto spriteBounds = sprite->getGlobalBounds();
	ship->InitHitboxComponent(10, 12, spriteBounds.width - 22, spriteBounds.height - 30);
}

const unsigned int Player::CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const
{
	if (position != lastPosition) {

		const auto y = lastPosition.y - position.y;
		const auto x = lastPosition.x - position.x;
		const auto angle = std::atan2(y, x) * (180.0 / M_PI);

		if (angle > 0)
		{
			return MOVING_UP;
		}
		else if (angle < 0)
		{
			return MOVING_DOWN;
		}
	}

	return IDLE;
}

void Player::Update(Input in, float dt) const
{
	const auto lastPosition = this->globalMovementComponent->GetPosition();
	const auto position = this->globalMovementComponent->Integrate(in, dt);
	const auto direction = this->CalculateDirection(position, lastPosition);

	this->group->Update(EntityUpdate(position, direction), dt);
}

void Player::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->group->Draw(target, interpPosition);
}