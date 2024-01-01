#include "player.h"

#include <iostream>

#include "util/math_utils.h"
#include "quad_tree/quad_tree.h"

#include "entity/i_entity_builder.h"
#include "entity/entity_object.h"
#include "entity/entity_update.h"

#include "player_input.h"
#include "components/movement/i_player_movement_component.h"
#include "components/attributes/i_player_attribute_component.h"
#include "components/collision_detection/i_collision_detection_component.h"

#include "bullet/collision.h"
#include "bullet/bullet.h"

#include "util/i_ray_caster.h"

Player::Player(
	std::unordered_map<PlayerObjects, std::shared_ptr<EntityObject>> objects,
	std::shared_ptr<IPlayerMovementComponent> globalMovementComponent,
	std::shared_ptr<IPlayerAttributeComponent> attributeComponent,
	std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent)
	: Entity<PlayerObjects>{ objects, globalMovementComponent, attributeComponent, collisionDetectionComponent, "player" }, movementComponent(globalMovementComponent), attributeComponent(attributeComponent)
{
	auto shipSprite = this->GetObject(PlayerObjects::SHIP)->GetSprite();
	shipSprite->setPosition(this->movementComponent->GetCenter());
	this->movementComponent->SetEntityAttributes(shipSprite->getPosition(), shipSprite->getGlobalBounds());

	this->mediators = std::make_shared<CollisionMediators>(
		CollisionMediators()
			.SetCollisionResolver([this](float damage, sf::Vector2f position) -> bool {
				this->attributeComponent->TakeDamage(damage, position);
				return this->attributeComponent->IsDead();
			})
			.SetPointTest([this](sf::Vector2f position, sf::Vector2f velocity, bool ray) -> std::shared_ptr<sf::Vector2f> {
				return this->DetectCollision(position, ray, velocity);
			})
			.SetZoneTest([this](sf::FloatRect& area) -> bool {
				return this->collisionDetectionComponent->DetectIntersection(area, this->GetObject(PlayerObjects::SHIP)->GetHitbox());
			})
    );
}

void Player::Update(const CollisionQuadTree& quadTree, Input& in, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto lastPosition = this->movementComponent->GetPosition();
	const auto position = this->movementComponent->Integrate(in, dt);
	const auto direction = Player::CalculateDirection(position, lastPosition);

	auto bounds = this->GetObject(PlayerObjects::SHIP)->GetSprite()->getLocalBounds();
	auto extent = sf::Vector2f(position.x + bounds.width, position.y + bounds.height);

	quadTree->Insert(std::make_shared<Point<CollisionMediators>>(position, this->GetTag(), this->mediators));
	quadTree->Insert(std::make_shared<Point<CollisionMediators>>(extent, this->GetTag(), this->mediators));

	auto shipConfig = this->bulletConfigs.at(PlayerObjects::SHIP);
	auto turrentConfig = this->bulletConfigs.at(PlayerObjects::TURRET);
	auto glowieConfig = this->bulletConfigs.at(PlayerObjects::GLOWIE);

	Entity::Update({
		{ PlayerObjects::SHIP, EntityUpdate(position, direction, *shipConfig, in.fire, false) },
		{ PlayerObjects::EXHAUST,  EntityUpdate(position, IDLE, *shipConfig, in.fire) },
		{ PlayerObjects::TURRET,  EntityUpdate(position, IDLE, *turrentConfig, in.fire) },
		{ PlayerObjects::GLOWIE,  EntityUpdate(position, IDLE, *glowieConfig, in.fire) }
	}, dt);

	this->attributeComponent->Update(dt);
}

void Player::Draw(const std::shared_ptr<IRenderer>& renderer, float interp) const
{
	Entity::Draw(renderer, this->movementComponent->Interpolate(interp));
}

unsigned int Player::CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition)
{
	if (position != lastPosition)
	{
		const auto y = lastPosition.y - position.y;
		const auto x = lastPosition.x - position.x;
		const auto angle = std::floor(AngleConversion::ToDegrees(atan2(y, x)));

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

void Player::InitBullets()
{
	auto bulletMediators = BulletMediators()
		.SetBulletResolver([&](bool kill, float damage) {
			if (kill) {
				this->attributeComponent->RegisterKill(damage);
			}
		})
		.SetPositionSampler([&]() -> sf::Vector2f {
			auto ship = this->GetObject(PlayerObjects::SHIP)->GetSprite();
			auto bounds = ship->getLocalBounds();
			auto position = ship->getPosition();
			position.x += bounds.width;
			return position;
		});

	this->bulletConfigs[PlayerObjects::SHIP] = std::make_shared<BulletConfig>(
        bulletMediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 4.0f)); }),
        this->GetTag(),
        sf::Color::Cyan,
        60.0f,
        0.0f,
        100.0f,
        AFFINITY::RIGHT,
        false,
        15.0f,
        0.5f
    );

	this->bulletConfigs[PlayerObjects::TURRET] = std::make_shared<BulletConfig>(
        bulletMediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(4.0f, 4); }),
        this->GetTag(),
        sf::Color::Yellow,
        90.0f,
        1.0f,
        400.0f,
        AFFINITY::RIGHT,
        false,
        5.0f
    );

	this->bulletConfigs[PlayerObjects::GLOWIE] = std::make_shared<BulletConfig>(
        bulletMediators.SetShapeBuilder([=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 5); }),
        this->GetTag(),
        sf::Color::Green,
        75.0f,
        5.0f,
        400.0f,
        AFFINITY::RIGHT,
        false,
        25.0f,
        3.0f
    );
}