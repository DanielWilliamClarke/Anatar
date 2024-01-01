#include <SFML/Graphics.hpp>

#include "player_entity_builder.h"

#include "util/i_texture_atlas.h"
#include "components/animation/animation_component.h"
#include "components/hitbox/hitbox_component.h"
#include "components/hitbox/inert_hitbox_component.h"
#include "components/movement/offset_movement_component.h"
#include "components/movement/orbital_movement_component.h"
#include "components/weapon/single/single_shot_weapon_component.h"
#include "components/weapon/burst/burst_shot_weapon_component.h"
#include "components/weapon/player/player_weapon_component.h"
#include "components/weapon/inert_weapon_component.h"
#include "components/weapon/beam/single_beam_weapon_component.h"
#include "entity/entity_object.h"

#include "bullet/types/projectile_factory.h"
#include "bullet/types/homing_projectile_factory.h"
#include "bullet/types/beam_factory.h"
#include "util/ray_caster.h"

PlayerEntityBuilder::PlayerEntityBuilder(std::shared_ptr<ITextureAtlas> textureAtlas, std::shared_ptr<IBulletSystem> bulletSystem, sf::FloatRect bounds)
	: textureAtlas(textureAtlas), bulletSystem(bulletSystem), bounds(bounds), rayCaster(std::make_shared<RayCaster>())
{}

EntityManifest<PlayerObjects> PlayerEntityBuilder::Build()
{
	auto texture = textureAtlas->GetTexture("playerShip");
	auto spriteScale = 2.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f((float)textureSize.x / 3, (float)textureSize.y / 2);
	auto origin = sf::Vector2f((float)spriteFrameSize.x / 2, (float)spriteFrameSize.y / 2);

	auto sprite = std::make_shared<sf::Sprite>();
	sprite->setOrigin(origin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
	sprite->setTexture(*texture);

	return {
		{ PlayerObjects::SHIP, this->BuildShip(sprite) },
		{ PlayerObjects::EXHAUST, this->BuildExhaust(sprite) },
		{ PlayerObjects::TURRET, this->BuildTurret(sprite) },
		{ PlayerObjects::GLOWIE, this->BuildGlowie(sprite) },
	};
}

std::shared_ptr<EntityObject> PlayerEntityBuilder::BuildShip(std::shared_ptr<sf::Sprite> shipSprite)
{
	auto texture = textureAtlas->GetTexture("playerShip");
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f((float)textureSize.x / 3, (float)textureSize.y / 2);

	auto animationComponent = std::make_shared<AnimationComponent>();
	animationComponent->SetAssets(shipSprite, texture);
	auto frameSize = sf::Vector2i((int)spriteFrameSize.x, (int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.2f, 0, 0, 0, 0, frameSize.x, frameSize.y);
	animationComponent->AddAnimation(this->MOVING_UP, 0.2f, 0, 1, 2, 1, frameSize.x, frameSize.y);
	animationComponent->AddAnimation(this->MOVING_DOWN, 0.2f, 0, 0, 2, 0, frameSize.x, frameSize.y);

	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Green);
	auto spriteBounds = shipSprite->getLocalBounds();
	hitboxComponent->Set(
		shipSprite->getPosition(),
		spriteBounds.left - spriteFrameSize.x / 2 - 8,
		spriteBounds.top - spriteFrameSize.y / 2,
		spriteFrameSize.x + 15,
		spriteFrameSize.y - 3); // All these magic numbers

	auto movementComponent = std::make_shared<OffSetMovementComponent>(shipSprite->getOrigin());

	auto beamFactory = std::make_shared<BeamFactory>(rayCaster, this->bounds, 0.5f);
	auto weaponComponent = std::make_shared<SingleBeamWeaponComponent>(bulletSystem, beamFactory, WeaponSlot::ONE, 2.0f, 1.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);

	return std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent, shipSprite);
}

std::shared_ptr<EntityObject> PlayerEntityBuilder::BuildExhaust(std::shared_ptr<sf::Sprite> shipSprite)
{
	auto texture = textureAtlas->GetTexture("playerExhaust");

	auto spriteScale = 2.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 2,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto sprite = std::make_shared<sf::Sprite>();
	sprite->setOrigin(spriteOrigin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
	sprite->setTexture(*texture);

	auto animationComponent = std::make_shared<AnimationComponent>();
	animationComponent->SetAssets(sprite, texture);
	auto frameSize = sf::Vector2i((int)spriteFrameSize.x, (int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.1f, 0, 0, 1, 0, frameSize.x, frameSize.y);

	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Green);

	auto movementComponent = std::make_shared<OffSetMovementComponent>(sf::Vector2f(-10.0, shipSprite->getOrigin().y + 2));

	auto weaponComponent = std::make_shared<InertWeaponComponent>();
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);

	return std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent, sprite);
}

std::shared_ptr<EntityObject> PlayerEntityBuilder::BuildTurret(std::shared_ptr<sf::Sprite> shipSprite)
{
	auto texture = textureAtlas->GetTexture("playerTurret");

	auto spriteScale = 1.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 4,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto sprite = std::make_shared<sf::Sprite>();
	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
	sprite->setTexture(*texture);

	auto animationComponent = std::make_shared<AnimationComponent>();
	animationComponent->SetAssets(sprite, texture);
	auto frameSize = sf::Vector2i((int)spriteFrameSize.x, (int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	auto hitboxComponent = std::make_shared<InertHitboxComponent>();

	auto bounds = shipSprite->getLocalBounds();
	auto offset = shipSprite->getOrigin() + sf::Vector2f(bounds.width, bounds.height);
	auto movementComponent = std::make_shared<OffSetMovementComponent>(offset);

	auto projectileFactory = std::make_shared<HomingProjectileFactory>();
	auto weaponComponent = std::make_shared<BurstShotWeaponComponent>(bulletSystem, projectileFactory, WeaponSlot::TWO, 2.0f, 0.0f, 10.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);

	return std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent, sprite);
}

std::shared_ptr<EntityObject> PlayerEntityBuilder::BuildGlowie(std::shared_ptr<sf::Sprite> shipSprite)
{
	auto texture = textureAtlas->GetTexture("playerGlowie");

	auto spriteScale = 1.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 7,
		(float)textureSize.y);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto sprite = std::make_shared<sf::Sprite>();
	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
	sprite->setTexture(*texture);

	auto animationComponent = std::make_shared<AnimationComponent>();
	animationComponent->SetAssets(sprite, texture);
	auto frameSize = sf::Vector2i((int)spriteFrameSize.x, (int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	auto hitboxComponent = std::make_shared<InertHitboxComponent>();

	auto movementComponent = std::make_shared<OrbitalMovementComponent>(shipSprite->getOrigin(), 75.0f, -100.0f);

	auto projectileFactory = std::make_shared<ProjectileFactory>();
	auto weaponComponent = std::make_shared<BurstShotWeaponComponent>(bulletSystem, projectileFactory, WeaponSlot::THREE, 15.0f, 10.0f, 90.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);

	return  std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent, sprite);
}