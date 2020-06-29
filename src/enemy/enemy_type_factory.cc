#include "enemy_type_factory.h"

#include <chrono>

#include "enemy.h"

#include "../components/animation/animation_component.h"
#include "../components/hitbox/hitbox_component.h"
#include "../components/movement/offset_movement_component.h"
#include "../components/movement/orbital_movement_component.h"
#include "../entity/entity_object.h"
#include "../components/movement/enemy_movement_component.h"
#include "util/random_number_mersenne_source.cc"

EnemyTypeFactory::EnemyTypeFactory(EnemyConfig config)
	: config(config)
{}

std::shared_ptr<Enemy> EnemyTypeFactory::Create()
{
    auto enemySpeed = 1000.0f;
	auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	auto randGenerator = std::make_shared<RandomNumberMersenneSource<int>>(seed);
    auto movementComponent = std::make_shared<EnemyMovementComponent>(config.motionConfig.bounds, config.motionConfig.enemySpeed, config.motionConfig.worldSpeed);
    return std::make_shared<Enemy>(config.builder(config), movementComponent, randGenerator);
}

EntityManifest EnemyTypeFactory::BuildLinearEnemy(EnemyConfig config)
{
	EntityManifest manifest;

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile(config.animationConfig.textureFile);

	auto totalFramesX = config.animationConfig.frames;
	auto spriteScale = config.animationConfig.scale;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / totalFramesX,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Red);
	auto movementComponent = std::make_shared<OffSetMovementComponent>(spriteOrigin);
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

	ship->AddAnimation(0, config.animationConfig.frameDuration, 0, 0, totalFramesX - 1, 0, frameSize.x, frameSize.y);

	manifest["enemy"] = ship;
	return manifest;
}

EntityManifest EnemyTypeFactory::BuildOribitalEnemy(EnemyConfig config)
{
	EntityManifest manifest;

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile(config.animationConfig.textureFile);

	auto totalFramesX = config.animationConfig.frames;
	auto spriteScale = config.animationConfig.scale;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / totalFramesX,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Red);
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(spriteOrigin, 50.0f, 100.f);
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

	ship->AddAnimation(0, config.animationConfig.frameDuration, 0, 0, totalFramesX - 1, 0, frameSize.x, frameSize.y);

	manifest["enemy"] = ship;
	return manifest;
}