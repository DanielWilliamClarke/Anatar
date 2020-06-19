#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

#include "player.h"

#include "entity/i_entity_builder.h"
#include "entity/entity_object.h"
#include "entity/entity_update.h"

#include "player_input.h"
#include "components/animation_component.h"
#include "components/hitbox_component.h"
#include "components/global_movement_component.h"

Player::Player(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<GlobalMovementComponent> globalMovementComponent)
	: Entity{ entityBuilder, globalMovementComponent }
{
	this->objects = this->entityBuilder->Build();

	auto shipSprite = this->GetObject("ship")->GetSprite();
	shipSprite->setPosition(this->globalMovementComponent->GetCenter());
	this->globalMovementComponent->SetEntityAttributes(shipSprite->getPosition(), shipSprite->getGlobalBounds());
}

const unsigned int Player::CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const
{
	if (position != lastPosition)
	{
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

	std::map<std::string, EntityUpdate> updates;
	updates["ship"] = EntityUpdate(position, direction);
	this->UpdateObjects(updates, dt);
}

void Player::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->DrawObjects(target, interpPosition);
}