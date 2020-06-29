#define _USE_MATH_DEFINES
#include <cmath>

#include "enemy.h"

#include "../entity/i_entity_builder.h"
#include "../entity/entity_object.h"

#include "../components/movement/i_global_movement_component.h"

Enemy::Enemy(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent)
	: Entity{ entityBuilder, globalMovementComponent }
{
	this->objects = this->entityBuilder->Build();

	auto enemy = this->GetObject("enemy")->GetSprite();
	auto bounds = this->globalMovementComponent->GetBounds();
	enemy->setPosition({ bounds.width, bounds.height / 2 });
	this->globalMovementComponent->SetEntityAttributes(enemy->getPosition(), enemy->getGlobalBounds());
}

void Enemy::Update(float dt) const
{
	const auto position = this->globalMovementComponent->Integrate(dt);

	this->UpdateObjects({
		{ "enemy", EntityUpdate(position, IDLE) },
	}, dt);
}

void Enemy::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->DrawObjects(target, interpPosition);
}

const unsigned int Enemy::CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const
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