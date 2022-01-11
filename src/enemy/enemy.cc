#define _USE_MATH_DEFINES
#include <cmath>

#include "enemy.h"

#include "entity/i_entity_builder.h"
#include "entity/entity_object.h"
#include "quad_tree/quad_tree.h"
#include "util/i_ray_caster.h"

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
	this->GetObject(EnemyObjects::ENEMY)->GetSprite()->setPosition(initialPosition);
	this->globalMovementComponent->SetEntityAttributes(initialPosition, this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getGlobalBounds());
}

void Enemy::Update(std::shared_ptr<QuadTree<Collision>> quadTree, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto position = this->globalMovementComponent->Integrate(dt);
	auto bounds = this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getLocalBounds();
	auto extent = sf::Vector2f(position.x + bounds.width, position.y + bounds.height);

	auto collisionTest = [this](sf::Vector2f position, sf::Vector2f velocity, bool ray) -> bool {
		if (ray) {
			return this->DetectCollisionWithRay(position, velocity)->intersects;
		} else {
			return this->DetectCollision(position);
		}
	};
	auto isInsideZone = [this](sf::FloatRect& area) -> bool { return this->IsInside(area); };
	auto collisionHandler = [this](float damage, sf::Vector2f position) { 
		this->TakeDamage(damage, position);
		return this->HasDied();
	};

	quadTree->Insert(std::make_shared<Point>(position, this->GetTag(), collisionTest, isInsideZone, collisionHandler));
	quadTree->Insert(std::make_shared<Point>(extent, this->GetTag(), collisionTest, isInsideZone, collisionHandler));

	auto config = this->bulletConfigs.at(EnemyObjects::ENEMY);
	this->UpdateObjects({
		{ EnemyObjects::ENEMY, EntityUpdate(position, IDLE, *config) },
	}, dt);
}

void Enemy::Draw(std::shared_ptr<IRenderer> renderer, float interp) const
{
	const auto interpPosition = this->globalMovementComponent->Interpolate(interp);
	this->DrawObjects(renderer, interpPosition);
}

void Enemy::InitBullets()
{
	this->bulletConfigs[EnemyObjects::ENEMY] = std::make_shared<BulletConfig>(
		BulletCallbacks(
			[=](bool kill, float damage) {},
			[this]() -> sf::Vector2f { return this->GetPosition(); },
			[=](void) -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 3); }),
		this->GetTag(),
		sf::Color::Red, 150.0f, 10.0f, 350.0f, AFFINITY::LEFT, false, 1.0f, 3.0f);
}

sf::Vector2f Enemy::GetPosition() const
{
	return this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getPosition();
}

bool Enemy::IsInside(sf::FloatRect& area) const
{
	return area.intersects(
		this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getGlobalBounds());
}