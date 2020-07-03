#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

#include "player.h"

#include "../entity/i_entity_builder.h"
#include "../entity/entity_object.h"
#include "../entity/entity_update.h"

#include "player_input.h"
#include "../components/movement/i_global_movement_component.h"

#include "../bullet/bullet.h"

Player::Player(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IPlayerMovementComponent> globalMovementComponent)
	: Entity{ entityBuilder, globalMovementComponent }, movementComponent(globalMovementComponent)
{
	this->objects = this->entityBuilder->Build();

	auto shipSprite = this->GetObject("ship")->GetSprite();
	shipSprite->setPosition(this->movementComponent->GetCenter());
	this->movementComponent->SetEntityAttributes(shipSprite->getPosition(), shipSprite->getGlobalBounds());
}

void Player::Update(Input& in, float dt) const
{
	const auto lastPosition = this->movementComponent->GetPosition();
	const auto position = this->movementComponent->Integrate(in, dt);
	const auto direction = this->CalculateDirection(position, lastPosition);

	//BulletConfig shipBulletConfig(std::make_shared<sf::CircleShape>(4.0f, 3), sf::Color::Cyan, 30.0f, 300.0f, false, 10.0f);
	BulletConfig shipBulletConfig(std::make_shared<sf::RectangleShape>(sf::Vector2f(50.0f, 2.0f)), sf::Color::Cyan, 0.0f, 300.0f, false, 10.0f);
	BulletConfig turretBulletConfig(std::make_shared<sf::CircleShape>(2.0f, 4), sf::Color::Yellow, 0.0f, 400.0f, false, 10.0f);

	this->UpdateObjects({
		{ "ship", EntityUpdate(position, direction, shipBulletConfig, in.fire, false) },
		{ "exhaust",  EntityUpdate(position, IDLE, shipBulletConfig, in.fire) },
		{ "turret",  EntityUpdate(position, IDLE, turretBulletConfig, in.fire) }
	}, dt);
}

void Player::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->movementComponent->Interpolate(interp);
	this->DrawObjects(target, interpPosition);
}

const unsigned int Player::CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const
{
	if (position != lastPosition)
	{
		const auto y = lastPosition.y - position.y;
		const auto x = lastPosition.x - position.x;
		const auto angle = std::floor(std::atan2(y, x) * (180.0 / M_PI));


		if (angle == 0 || angle == 180)
		{
			return IDLE;
		}
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