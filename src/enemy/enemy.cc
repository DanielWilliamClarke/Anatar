#define _USE_MATH_DEFINES
#include <cmath>

#include "enemy.h"

#include "entity/i_entity_builder.h"
#include "entity/entity_object.h"
#include "quad_tree/quad_tree.h"
#include "util/i_ray_caster.h"

#include "components/movement/i_global_movement_component.h"
#include "components/collision_detection/i_collision_detection_component.h"

#include "bullet/collision.h"
#include "bullet/bullet.h"

Enemy::Enemy(
	std::map<EnemyObjects, std::shared_ptr<EntityObject>> manifest,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
	std::shared_ptr<IAttributeComponent> attributeComponent,
	std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent,
	sf::Vector2f initialPosition)
	: Entity<EnemyObjects>{ globalMovementComponent, attributeComponent, collisionDetectionComponent, "enemy" }
{
	this->objects = manifest;
	this->GetObject(EnemyObjects::ENEMY)->GetSprite()->setPosition(initialPosition);
	this->globalMovementComponent->SetEntityAttributes(initialPosition, this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getGlobalBounds());

	this->mediators = std::make_shared<CollisionMediators>(
		CollisionMediators()
			.Inject([this](float damage, sf::Vector2f position) -> bool {
				this->attributeComponent->TakeDamage(damage, position);
				return this->attributeComponent->IsDead();
			})
			.Inject([this](sf::Vector2f position, sf::Vector2f velocity, bool ray) -> std::shared_ptr<sf::Vector2f> {
				return this->DetectCollision(position, ray, velocity);
			})
			.Inject([this](sf::FloatRect& area) -> bool {
				return this->collisionDetectionComponent->DetechIntersection(area, this->GetObject(EnemyObjects::ENEMY)->GetHitbox());
			}));
}

void Enemy::Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto position = this->globalMovementComponent->Integrate(dt);
	auto bounds = this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getLocalBounds();
	auto extent = sf::Vector2f(position.x + bounds.width, position.y + bounds.height);

	quadTree->Insert(std::make_shared<Point<CollisionMediators>>(position, this->GetTag(), this->mediators));
	quadTree->Insert(std::make_shared<Point<CollisionMediators>>(extent, this->GetTag(), this->mediators));

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
		BulletMediators()
			.Inject([=](bool kill, float damage) {})
			.Inject([this]() -> sf::Vector2f { return this->GetObject(EnemyObjects::ENEMY)->GetSprite()->getPosition(); })
			.Inject([=](void) -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 3); }),
		this->GetTag(),
		sf::Color::Red, 150.0f, 10.0f, 350.0f, AFFINITY::LEFT, false, 1.0f, 3.0f);
}