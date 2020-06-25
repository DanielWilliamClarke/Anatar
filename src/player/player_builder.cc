#include <SFML/Graphics.hpp>

#include "player_builder.h"

#include "../components/animation/animation_component.h"
#include "../components/hitbox/hitbox_component.h"
#include "../components/movement/offset_movement_component.h"
#include "../components/movement/orbital_movement_component.h"
#include "../entity/entity_object.h"

EntityManifest PlayerBuilder::Build()
{
	this->BuildShip();
	this->BuildExhaust();
	this->BuildTurret();
	return manifest;
}

void PlayerBuilder::BuildShip()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/viperFrames.png");

	auto spriteScale = 2.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 3,
		(float)textureSize.y / 2);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();
	auto movementComponent = std::make_shared<OffSetMovementComponent>(spriteOrigin);
	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);

	auto sprite = ship->GetSprite();
	ship->SetTexture(texture);
	ship->InitAnimationComponent(texture);
	sprite->setOrigin(spriteOrigin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	auto spriteBounds = sprite->getLocalBounds();
	ship->InitHitboxComponent(
		spriteBounds.left - spriteFrameSize.x / 2 - 8,
		spriteBounds.top - spriteFrameSize.y / 2,
		spriteFrameSize.x + 15,
		spriteFrameSize.y - 3); // All these magic numbers

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);

	ship->AddAnimation(this->IDLE, 0.2f, 0, 0, 0, 0, frameSize.x, frameSize.y);
	ship->AddAnimation(this->MOVING_UP, 0.2f, 0, 1, 2, 1, frameSize.x, frameSize.y);
	ship->AddAnimation(this->MOVING_DOWN, 0.2f, 0, 0, 2, 0, frameSize.x, frameSize.y);

	manifest["ship"] = ship;
}

void PlayerBuilder::BuildExhaust()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/viperExhaust.png");

	auto spriteScale = 2.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 2,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto shipSpriteOrigin = manifest.at("ship")->GetSprite()->getOrigin();

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();
	auto movementComponent = std::make_shared<OffSetMovementComponent>(sf::Vector2f(-10.0, shipSpriteOrigin.y + 2));

	auto exhaust = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);
	auto sprite = exhaust->GetSprite();

	exhaust->SetTexture(texture);
	exhaust->InitAnimationComponent(texture);
	sprite->setOrigin(spriteOrigin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);

	exhaust->AddAnimation(this->IDLE, 0.1f, 0, 0, 1, 0, frameSize.x, frameSize.y);

	manifest["exhaust"] = exhaust;
}

void PlayerBuilder::BuildTurret()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/viperTurret.png");

	auto spriteScale = 1.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 4,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto shipSpriteOrigin = manifest.at("ship")->GetSprite()->getOrigin();

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(shipSpriteOrigin, 50.0f, 100.0f);

	auto turret = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);
	auto sprite = turret->GetSprite();
	turret->SetTexture(texture);
	turret->InitAnimationComponent(texture);
	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	auto spriteBounds = sprite->getLocalBounds();
	turret->InitHitboxComponent(
		spriteBounds.left - spriteFrameSize.x / 2,
		spriteBounds.top - spriteFrameSize.y / 2,
		spriteFrameSize.x,
		spriteFrameSize.y);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);

	turret->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	manifest["turret"] = turret;
}