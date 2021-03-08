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

void Enemy::Update(std::shared_ptr<QuadTree<std::shared_ptr<Entity>, EntityCollision>> quadTree, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto position = this->globalMovementComponent->Integrate(dt);

	auto bounds = this->GetObject("enemy")->GetSprite()->getLocalBounds();
	auto extent = sf::Vector2f(position.x + bounds.width, position.y + bounds.height);
	quadTree->Insert(Point<std::shared_ptr<Entity>>(position, shared_from_this()));
	quadTree->Insert(Point<std::shared_ptr<Entity>>(extent, shared_from_this()));

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
	this->bulletConfigs["enemy"] = std::make_shared<BulletConfig>(shared_from_this(),
		[=](void) -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 3); },
		sf::Color::Red, 150.0f, 10.0f, 350.0f, AFFINITY::LEFT, false, 1.0f, 3.0f);
}

sf::Vector2f Enemy::GetPosition() const
{
	auto enemy = this->GetObject("enemy")->GetSprite();
	auto bounds = enemy->getLocalBounds();
	auto position = enemy->getPosition();

	position.x += bounds.width / 2;
	position.y += bounds.height / 2;

	return position;
}