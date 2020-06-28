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

	auto shipSprite = this->GetObject("enemy")->GetSprite();
	shipSprite->setPosition(this->globalMovementComponent->GetCenter());
	this->globalMovementComponent->SetEntityAttributes(shipSprite->getPosition(), shipSprite->getGlobalBounds());
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