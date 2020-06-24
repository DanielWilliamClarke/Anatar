#include <SFML/Graphics.hpp>

#include "player_builder.h"

#include "../components/animation/animation_component.h"
#include "../components/hitbox/hitbox_component.h"
#include "../components/movement/offset_movement_component.h"
#include "../components/movement/orbital_movement_component.h"
#include "../entity/entity_object.h"

EntityManifest PlayerBuilder::Build() const
{
	EntityManifest manifest;
	return {
		{ "ship", this->BuildShip() },
		{ "exhaust", this->BuildExhaust() },
		{ "turret", this->BuildTurret() }
	};
}

std::shared_ptr<EntityObject> PlayerBuilder::BuildShip() const
{
	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();
	auto movementComponent = std::make_shared<OffSetMovementComponent>(sf::Vector2f(.0f, .0f));

	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);
	auto sprite = ship->GetSprite();

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/viperFrames.png");
	ship->SetTexture(texture);
	ship->InitAnimationComponent(texture);

	auto spriteTextureSize = std::make_pair(33, 26);
	auto spriteScale = 2.0f;

	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	ship->AddAnimation(this->IDLE, 0.2f, 0, 0, 0, 0, spriteTextureSize.first, spriteTextureSize.second);
	ship->AddAnimation(this->MOVING_UP, 0.2f, 0, 1, 2, 1, spriteTextureSize.first, spriteTextureSize.second);
	ship->AddAnimation(this->MOVING_DOWN, 0.2f, 0, 0, 2, 0, spriteTextureSize.first, spriteTextureSize.second);

	auto spriteBounds = sprite->getGlobalBounds();
	ship->InitHitboxComponent(10, 12, spriteBounds.width - 22, spriteBounds.height - 30);

	return ship;
}

std::shared_ptr<EntityObject> PlayerBuilder::BuildExhaust() const
{
	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();
	auto movementComponent = std::make_shared<OffSetMovementComponent>(sf::Vector2f(.0f, 11.0f));

	auto exhaust = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);
	auto sprite = exhaust->GetSprite();

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/viperExhaust.png");
	exhaust->SetTexture(texture);
	exhaust->InitAnimationComponent(texture);

	auto spriteTextureSize = std::make_pair(6, 16);
	auto spriteScale = 2.0f;

	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
	exhaust->AddAnimation(this->IDLE, 0.2f, 0, 0, 1, 0, spriteTextureSize.first, spriteTextureSize.second);
	animationComponent->Play(this->IDLE);

	return exhaust;
}

std::shared_ptr<EntityObject> PlayerBuilder::BuildTurret() const
{
	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(sf::Vector2f(16.5f, 13.0f), 50.0f, 100.0f);

	auto turret = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent);
	auto sprite = turret->GetSprite();

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("assets/viperTurret.png");
	turret->SetTexture(texture);
	turret->InitAnimationComponent(texture);

	auto spriteTextureSize = std::make_pair(16, 16);
	auto spriteScale = 1.0f;

	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
	turret->AddAnimation(this->IDLE, 0.2f, 0, 0, 3, 0, spriteTextureSize.first, spriteTextureSize.second);
	animationComponent->Play(this->IDLE);

	auto spriteBounds = sprite->getGlobalBounds();
	turret->InitHitboxComponent(0, 0, spriteBounds.width, spriteBounds.height);

	return turret;
}