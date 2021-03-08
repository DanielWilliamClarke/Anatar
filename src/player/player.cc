#include "player.h"

#include <iostream>

#include "util/math_utils.h"

#include "entity/i_entity_builder.h"
#include "entity/entity_object.h"
#include "entity/entity_update.h"

#include "player_input.h"
#include "components/movement/i_player_movement_component.h"
#include "components/attributes/i_player_attribute_component.h"
#include "bullet/bullet.h"

Player::Player(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IPlayerMovementComponent> globalMovementComponent,
	std::shared_ptr<IPlayerAttributeComponent> attributeComponent)
	: Entity{ entityBuilder, globalMovementComponent, attributeComponent, "player" }, movementComponent(globalMovementComponent), attributeComponent(attributeComponent)
{
	this->objects = this->entityBuilder->Build();

	auto shipSprite = this->GetObject("ship")->GetSprite();
	shipSprite->setPosition(this->movementComponent->GetCenter());
	this->movementComponent->SetEntityAttributes(shipSprite->getPosition(), shipSprite->getGlobalBounds());
}

void Player::Update(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree, Input& in, float dt)
{
	if (this->bulletConfigs.empty())
	{
		this->InitBullets();
	}

	const auto lastPosition = this->movementComponent->GetPosition();
	const auto position = this->movementComponent->Integrate(in, dt);
	const auto direction = this->CalculateDirection(position, lastPosition);

	quadTree->Insert(
		Point<std::shared_ptr<Entity>>(position, shared_from_this()));

	auto shipConfig = this->bulletConfigs.at("ship");
	auto turrentConfig = this->bulletConfigs.at("turret");
	auto glowieConfig = this->bulletConfigs.at("glowie");

	this->UpdateObjects({
		{ "ship", EntityUpdate(position, direction, *shipConfig, in.fire, false) },
		{ "exhaust",  EntityUpdate(position, IDLE, *shipConfig, in.fire) },
		{ "turret",  EntityUpdate(position, IDLE, *turrentConfig, in.fire) },
		{ "glowie",  EntityUpdate(position, IDLE, *glowieConfig, in.fire) }
	}, dt);

	this->attributeComponent->Update(dt);
}

void Player::Draw(sf::RenderTarget& target, float interp) const
{
	const auto interpPosition = this->movementComponent->Interpolate(interp);
	this->DrawObjects(target, interpPosition);
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
	auto self = shared_from_this();

	this->bulletConfigs["ship"] = std::make_shared<BulletConfig>(self,
		[=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 4.0f)); },
		sf::Color::Cyan, 60.0f, 0.0f, 100.0f, AFFINITY::RIGHT, false, 15.0f, 0.5f);

	this->bulletConfigs["turret"] = std::make_shared<BulletConfig>(self,
		[=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(4.0f, 4); },
		sf::Color::Yellow, 90.0f, 1.0f, 400.0f, AFFINITY::RIGHT, false, 5.0f);

	this->bulletConfigs["glowie"] = std::make_shared<BulletConfig>(self,
		[=]() -> std::shared_ptr<sf::Shape> { return std::make_shared<sf::CircleShape>(5.0f, 5); },
		sf::Color::Green, 75.0f, 5.0f, 400.0f, AFFINITY::RIGHT, false, 25.0f, 3.0f);
}

sf::Vector2f Player::GetPosition() const
{
	auto ship = this->GetObject("ship")->GetSprite();
	auto bounds = ship->getLocalBounds();
	auto position = ship->getPosition();
	position.x += bounds.width;
	return position;
}