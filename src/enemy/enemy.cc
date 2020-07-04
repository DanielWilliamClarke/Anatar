#define _USE_MATH_DEFINES
#include <cmath>

#include "enemy.h"

#include "../entity/i_entity_builder.h"
#include "../entity/entity_object.h"

#include "../components/movement/i_global_movement_component.h"
#include "../bullet/bullet.h"

Enemy::Enemy(
	EntityManifest manifest,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
	sf::Vector2f initialPosition)
	: Entity{ nullptr, globalMovementComponent }
{
	this->objects = manifest;
	this->GetObject("enemy")->GetSprite()->setPosition(initialPosition);
	this->globalMovementComponent->SetEntityAttributes(initialPosition, this->GetObject("enemy")->GetSprite()->getGlobalBounds());
}

void Enemy::Update(float dt) const
{
	const auto position = this->globalMovementComponent->Integrate(dt);

	auto shapeBuilder = [=](void) -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 3); };
	BulletConfig bulletConfig(shapeBuilder, sf::Color::Red, 10.0f, 350.0f, false, 10.0f);

	this->UpdateObjects({
		{ "enemy", EntityUpdate(position, IDLE, bulletConfig) },
	}, dt);
}

void Enemy::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->DrawObjects(target, interpPosition);
}