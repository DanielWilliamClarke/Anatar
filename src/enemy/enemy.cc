#define _USE_MATH_DEFINES
#include <cmath>

#include "enemy.h"

#include "entity/i_entity_builder.h"
#include "entity/entity_object.h"

#include "components/movement/i_global_movement_component.h"
#include "bullet/bullet.h"

Enemy::Enemy(
	EntityManifest manifest,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
	std::shared_ptr<IAttributeComponent> attributeComponent,
	sf::Vector2f initialPosition)
	: Entity{ nullptr, globalMovementComponent, attributeComponent }
{
	this->objects = manifest;
	this->GetObject("enemy")->GetSprite()->setPosition(initialPosition);
	this->globalMovementComponent->SetEntityAttributes(initialPosition, this->GetObject("enemy")->GetSprite()->getGlobalBounds());
}

void Enemy::Update(float dt) 
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto position = this->globalMovementComponent->Integrate(dt);
	auto config = this->bulletConfigs.at("enemy");
	this->UpdateObjects({
		{ "enemy", EntityUpdate(position, IDLE, *config) },
	}, dt);
}

void Enemy::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->DrawObjects(target, interpPosition);
}

void Enemy::InitBullets()
{
	std::shared_ptr<Entity> self = shared_from_this();
	this->bulletConfigs["enemy"] = std::make_shared<BulletConfig>(self,
		[=](void) -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 3); },
		sf::Color::Red, 150.0f, 10.0f, 350.0f, false, 10.0f, 3.0f);
} 