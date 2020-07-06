#include "enemy_type_factory.h"

#include <chrono>

#include "enemy.h"

#include "util/random_number_mersenne_source.cc"

#include "../components/animation/animation_component.h"
#include "../components/hitbox/hitbox_component.h"
#include "../components/movement/offset_movement_component.h"
#include "../components/movement/orbital_movement_component.h"
#include "../components/movement/enemy_movement_component.h"
#include "../components/attributes/health_attribute_component.h"
#include "../components/weapon/i_weapon_component_factory.h"

#include "../entity/entity_object.h"

EnemyTypeFactory::EnemyTypeFactory(EnemyConfig config)
	: config(config)
{}

std::shared_ptr<Entity> EnemyTypeFactory::Create()
{
    auto movementComponent = std::make_shared<EnemyMovementComponent>(config.motionConfig.bounds, config.motionConfig.enemySpeed, config.motionConfig.worldSpeed);
	auto attributeComponent = std::make_shared<HealthAttributeComponent>(30.0f, 0.0f);

	auto textureSize = config.animationConfig.texture->getSize();
	auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	auto randGenerator = std::make_shared<RandomNumberMersenneSource<int>>(seed);
	auto position = sf::Vector2f(
		config.motionConfig.bounds.width,
		(float)randGenerator->Generate((int)config.motionConfig.bounds.top, (int)config.motionConfig.bounds.height - textureSize.y));
    return std::make_shared<Enemy>(config.builder(config), movementComponent, attributeComponent, position);
}

EntityManifest EnemyTypeFactory::BuildLinearEnemy(EnemyConfig config)
{
	auto textureSize = config.animationConfig.texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / config.animationConfig.frames,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	return EnemyTypeFactory::BuildEnemy(config, std::make_shared<OffSetMovementComponent>(spriteOrigin));
}

EntityManifest EnemyTypeFactory::BuildOribitalEnemy(EnemyConfig config)
{
	auto textureSize = config.animationConfig.texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / config.animationConfig.frames,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	return EnemyTypeFactory::BuildEnemy(config, std::make_shared<OrbitalMovementComponent>(spriteOrigin, 25.0f, 200.f));
}

EntityManifest EnemyTypeFactory::BuildEnemy(EnemyConfig config, std::shared_ptr<ILocalMovementComponent> movementComponent)
{
	auto textureSize = config.animationConfig.texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / config.animationConfig.frames,
		(float)textureSize.y);

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Red);
	auto weaponComponent = config.weaponConfig.weaponComponentFactory->Construct(config.weaponConfig.bulletSystem, config.weaponConfig.delay);
	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, weaponComponent);

	ship->SetTexture(config.animationConfig.texture);
	ship->InitAnimationComponent(config.animationConfig.texture);

	auto sprite = ship->GetSprite();
	sprite->setOrigin(sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2));
	sprite->setScale(sf::Vector2f(
		config.animationConfig.scale,
		config.animationConfig.scale));

	auto spriteBounds = sprite->getLocalBounds();
	ship->InitHitboxComponent(
		spriteBounds.left - spriteFrameSize.x / 2,
		spriteBounds.top - spriteFrameSize.y / 2,
		spriteFrameSize.x,
		spriteFrameSize.y);

	ship->AddAnimation(0, config.animationConfig.frameDuration, 0, 0, config.animationConfig.frames - 1, 0, (int)spriteFrameSize.x, (int)spriteFrameSize.y);

	EntityManifest manifest;
	manifest["enemy"] = ship;
	return manifest;
}