#include <SFML/Graphics.hpp>

#include "enemy_builder.h"

#include "../components/animation/animation_component.h"
#include "../components/hitbox/hitbox_component.h"
#include "../components/movement/orbital_movement_component.h"
#include "../entity/entity_object.h"

EntityManifest EnemyBuilder::Build()
{
	this->BuildEnemy();
	return manifest;
}

void EnemyBuilder::BuildEnemy()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/enemy_1.png");

	auto spriteScale = 2.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 6,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Red);
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(spriteOrigin, 100.0f, 100.0f);
	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);

	auto sprite = ship->GetSprite();
	ship->SetTexture(texture);
	ship->InitAnimationComponent(texture);
	sprite->setOrigin(spriteOrigin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	auto spriteBounds = sprite->getLocalBounds();
	ship->InitHitboxComponent(
		spriteBounds.left - spriteFrameSize.x / 2,
		spriteBounds.top - spriteFrameSize.y / 2,
		spriteFrameSize.x,
		spriteFrameSize.y); // All these magic numbers

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);

	ship->AddAnimation(this->IDLE, 0.2f, 0, 0, 5, 0, frameSize.x, frameSize.y);

	manifest["enemy"] = ship;
}