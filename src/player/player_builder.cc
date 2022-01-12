#include <SFML/Graphics.hpp>

#include "player_builder.h"

#include "util/i_texture_atlas.h"
#include "components/animation/animation_component.h"
#include "components/hitbox/hitbox_component.h"
#include <components\hitbox\inert_hitbox_component.h>
#include "components/movement/offset_movement_component.h"
#include "components/movement/orbital_movement_component.h"
#include "components/weapon/single/single_shot_weapon_component.h"
#include "components/weapon/burst/burst_shot_weapon_component.h"
#include "components/weapon/player/player_weapon_component.h"
#include "components/weapon/inert_weapon_component.h"
#include "components/weapon/beam/single_beam_weapon_component.h"
#include "components/weapon/beam/radial_beam_weapon_component.h"
#include "entity/entity_object.h"

#include "bullet/types/projectile_factory.h"
#include "bullet/types/homing_projectile_factory.h"
#include "bullet/types/beam_factory.h"
#include "util/ray_caster.h"

PlayerBuilder::PlayerBuilder(std::shared_ptr<ITextureAtlas> textureAtlas, std::shared_ptr<IBulletSystem> bulletSystem, sf::FloatRect bounds)
	: textureAtlas(textureAtlas), bulletSystem(bulletSystem), bounds(bounds), rayCaster(std::make_shared<RayCaster>())
{}

EntityManifest PlayerBuilder::Build()
{
	this->BuildShip();
	this->BuildExhaust();
	this->BuildTurret();
	this->BuildGlowie();
	return manifest;
}

void PlayerBuilder::BuildShip()
{
	auto texture = textureAtlas->GetTexture("playerShip");

	auto spriteScale = 2.0f;
	auto textureSize = texture->getSize();
	auto spriteFrameSize = sf::Vector2f(
		(float)textureSize.x / 3,
		(float)textureSize.y / 2);
	auto spriteOrigin = sf::Vector2f(
		spriteFrameSize.x / 2,
		spriteFrameSize.y / 2);

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Green);
	auto movementComponent = std::make_shared<OffSetMovementComponent>(spriteOrigin);

	auto beamFactory = std::make_shared<BeamFactory>(rayCaster, this->bounds, 0.5f);
	auto weaponComponent = std::make_shared<RadialBeamWeaponComponent>(bulletSystem, beamFactory, 2.0f, 1.0f, 5.0f, 2.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);

	auto sprite = ship->GetSprite();

	sprite->setOrigin(spriteOrigin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	sprite->setTexture(*texture);
	animationComponent->SetAssets(sprite, texture);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.2f, 0, 0, 0, 0, frameSize.x, frameSize.y);
	animationComponent->AddAnimation(this->MOVING_UP, 0.2f, 0, 1, 2, 1, frameSize.x, frameSize.y);
	animationComponent->AddAnimation(this->MOVING_DOWN, 0.2f, 0, 0, 2, 0, frameSize.x, frameSize.y);

	auto spriteBounds = sprite->getLocalBounds();
	hitboxComponent->Set(
		sprite->getPosition(),
		spriteBounds.left - spriteFrameSize.x / 2 - 8,
		spriteBounds.top - spriteFrameSize.y / 2,
		spriteFrameSize.x + 15,
		spriteFrameSize.y - 3); // All these magic numbers

	manifest[PlayerObjects::SHIP] = ship;
}

void PlayerBuilder::BuildExhaust()
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

	auto shipSpriteOrigin = manifest.at(PlayerObjects::SHIP)->GetSprite()->getOrigin();

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Green);
	auto movementComponent = std::make_shared<OffSetMovementComponent>(sf::Vector2f(-10.0, shipSpriteOrigin.y + 2));
	auto weaponComponent = std::make_shared<InertWeaponComponent>();
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto exhaust = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);
	auto sprite = exhaust->GetSprite();

	sprite->setOrigin(spriteOrigin);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	sprite->setTexture(*texture);
	animationComponent->SetAssets(sprite, texture);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.1f, 0, 0, 1, 0, frameSize.x, frameSize.y);

	manifest[PlayerObjects::EXHAUST] = exhaust;
}

void PlayerBuilder::BuildTurret()
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

	auto shipSprite = manifest.at(PlayerObjects::SHIP)->GetSprite();
	auto bounds = shipSprite->getLocalBounds();
	auto offset = shipSprite->getOrigin();
	offset.x += bounds.width;
	offset.y += bounds.height;

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<InertHitboxComponent>();
	auto movementComponent = std::make_shared<OffSetMovementComponent>(offset);
	auto projectileFactory = std::make_shared<HomingProjectileFactory>();
	auto weaponComponent = std::make_shared<BurstShotWeaponComponent>(bulletSystem, projectileFactory, 2.0f, 0.0f, 10.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto turret = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);
	auto sprite = turret->GetSprite();

	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	sprite->setTexture(*texture);
	animationComponent->SetAssets(sprite, texture);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	manifest[PlayerObjects::TURRET] = turret;
}

void PlayerBuilder::BuildGlowie()
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

	auto shipSpriteOrigin = manifest.at(PlayerObjects::SHIP)->GetSprite()->getOrigin();

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<InertHitboxComponent>();
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(shipSpriteOrigin, 75.0f, -100.0f);
	auto projectileFactory = std::make_shared<ProjectileFactory>();
	auto weaponComponent = std::make_shared<BurstShotWeaponComponent>(bulletSystem, projectileFactory, 15.0f, 10.0f, 90.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto glowie = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);
	auto sprite = glowie->GetSprite();

	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	sprite->setTexture(*texture);
	animationComponent->SetAssets(sprite, texture);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);
	animationComponent->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	manifest[PlayerObjects::GLOWIE] = glowie;
}