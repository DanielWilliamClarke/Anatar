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
#include "bullet/bullet.h"

#include "util/i_ray_caster.h"

Player::Player(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IPlayerMovementComponent> globalMovementComponent,
	std::shared_ptr<IPlayerAttributeComponent> attributeComponent)
	: Entity{ entityBuilder, globalMovementComponent, attributeComponent, "player" }, movementComponent(globalMovementComponent), attributeComponent(attributeComponent)
{
	this->objects = this->entityBuilder->Build();

	auto shipSprite = this->GetObject(SHIP)->GetSprite();
	shipSprite->setPosition(this->movementComponent->GetCenter());
	this->movementComponent->SetEntityAttributes(shipSprite->getPosition(), shipSprite->getGlobalBounds());
}

void Player::Update(std::shared_ptr<QuadTree<Collision>> quadTree, Input& in, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto lastPosition = this->movementComponent->GetPosition();
	const auto position = this->movementComponent->Integrate(in, dt);
	const auto direction = this->CalculateDirection(position, lastPosition);

	auto bounds = this->GetObject(SHIP)->GetSprite()->getLocalBounds();
	auto extent = sf::Vector2f(position.x + bounds.width, position.y + bounds.height);

	auto collisionTest = [this](sf::Vector2f position, sf::Vector2f velocity, bool ray) -> bool {
		if (ray) {
			return this->DetectCollisionWithRay(position, velocity)->intersects;
		}
		else {
			return this->DetectCollision(position);
		}
	};

	auto isInsideZone = [this](sf::FloatRect& area) -> bool { return this->IsInside(area); };
	auto collisionHandler = [this](float damage, sf::Vector2f position) -> bool { 
		this->TakeDamage(damage, position);
		return this->HasDied();
	};

	quadTree->Insert(std::make_shared<Point>(position, this->GetTag(), collisionTest, isInsideZone, collisionHandler));
	quadTree->Insert(std::make_shared<Point>(extent, this->GetTag(), collisionTest, isInsideZone, collisionHandler));

	auto shipConfig = this->bulletConfigs.at(SHIP);
	auto turrentConfig = this->bulletConfigs.at(TURRET);
	auto glowieConfig = this->bulletConfigs.at(GLOWIE);

	this->UpdateObjects({
		{ SHIP, EntityUpdate(position, direction, *shipConfig, in.fire, false) },
		{ EXHAUST,  EntityUpdate(position, IDLE, *shipConfig, in.fire) },
		{ TURRET,  EntityUpdate(position, IDLE, *turrentConfig, in.fire) },
		{ GLOWIE,  EntityUpdate(position, IDLE, *glowieConfig, in.fire) }
	}, dt);

	this->attributeComponent->Update(dt);
}

void Player::Draw(std::shared_ptr<IRenderer> renderer, float interp) const
{
	const auto interpPosition = this->movementComponent->Interpolate(interp);
	this->DrawObjects(renderer, interpPosition);
}

const unsigned int Player::CalculateDirection(sf::Vector2f position, sf::Vector2f lastPosition) const
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
	auto collisionResolver = [this](bool kill, float damage) {
		if (kill) {
			this->RegisterKill(damage);
		}
	};
	auto positionSampler = [this]() -> sf::Vector2f { return this->GetPosition(); };

	this->bulletConfigs[SHIP] = std::make_shared<BulletConfig>(
		BulletCallbacks(
			collisionResolver,
			positionSampler,
			[=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 4.0f)); }),
		this->GetTag(), 
		sf::Color::Cyan, 60.0f, 0.0f, 100.0f, AFFINITY::RIGHT, false, 15.0f, 0.5f);

	this->bulletConfigs[TURRET] = std::make_shared<BulletConfig>(
		BulletCallbacks(
			collisionResolver,
			positionSampler,
			[=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(4.0f, 4); }),
		this->GetTag(),
		sf::Color::Yellow, 90.0f, 1.0f, 400.0f, AFFINITY::RIGHT, false, 5.0f);

	this->bulletConfigs[GLOWIE] = std::make_shared<BulletConfig>(
		BulletCallbacks(
			collisionResolver,
			positionSampler,
			[=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 5); }),
		this->GetTag(),
		sf::Color::Green, 75.0f, 5.0f, 400.0f, AFFINITY::RIGHT, false, 25.0f, 3.0f);
}

sf::Vector2f Player::GetPosition() const
{
	auto ship = this->GetObject(PlayerObjects::SHIP)->GetSprite();
	auto bounds = ship->getLocalBounds();
	auto position = ship->getPosition();
	position.x += bounds.width;
	return position;
}

bool Player::IsInside(sf::FloatRect& area) const
{
	return area.intersects(
		this->GetObject(SHIP)->GetSprite()->getGlobalBounds());
}