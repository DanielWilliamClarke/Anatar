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
	: Entity{ nullptr, globalMovementComponent, attributeComponent, "enemy" }
{
	this->objects = manifest;
	this->GetObject("enemy")->GetSprite()->setPosition(initialPosition);
	this->globalMovementComponent->SetEntityAttributes(initialPosition, this->GetObject("enemy")->GetSprite()->getGlobalBounds());
}

void Enemy::Update(std::shared_ptr<CollisionQuadTree> quadTree, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto position = this->globalMovementComponent->Integrate(dt);

	auto bounds = this->GetObject("enemy")->GetSprite()->getLocalBounds();
	auto extent = sf::Vector2f(position.x + bounds.width, position.y + bounds.height);
	quadTree->Insert(Point<Entity>(position, shared_from_this()));
	quadTree->Insert(Point<Entity>(extent, shared_from_this()));

	auto config = this->bulletConfigs.at("enemy");
	this->UpdateObjects({
		{ "enemy", EntityUpdate(position, IDLE, *config) },
	}, dt);
}

void Enemy::Draw(std::shared_ptr<IRenderer> renderer, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->DrawObjects(renderer, interpPosition);
}

void Enemy::InitBullets()
{
	this->bulletConfigs["enemy"] = std::make_shared<BulletConfig>(shared_from_this(),
		[=](void) -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 3); },
		sf::Color::Red, 150.0f, 10.0f, 350.0f, AFFINITY::LEFT, false, 1.0f, 1.0f);
}

sf::Vector2f Enemy::GetPosition() const
{
	return this->GetObject("enemy")->GetSprite()->getPosition();
}

bool Enemy::IsInside(sf::FloatRect& area) const
{
	return area.intersects(
		this->GetObject("enemy")->GetSprite()->getGlobalBounds());
}