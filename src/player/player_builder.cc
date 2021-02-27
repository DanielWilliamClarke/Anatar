#include <SFML/Graphics.hpp>

#include "player_builder.h"

#include "../util/i_texture_atlas.h"
#include "../components/animation/animation_component.h"
#include "../components/hitbox/hitbox_component.h"
#include "../components/movement/offset_movement_component.h"
#include "../components/movement/orbital_movement_component.h"
#include "../components/weapon/single/single_shot_weapon_component.h"
#include "../components/weapon/burst/burst_shot_weapon_component.h"
#include "../components/weapon/player/player_weapon_component.h"
#include "../components/weapon/inert_weapon_component.h"
#include "../components/weapon/beam/single_beam_weapon_component.h"
#include "../entity/entity_object.h"

#include "../bullet/projectile_factory.h"
#include "../bullet/beam_factory.h"

PlayerBuilder::PlayerBuilder(std::shared_ptr<ITextureAtlas> textureAtlas, std::shared_ptr<IBulletSystem> bulletSystem, sf::FloatRect bounds)
	: textureAtlas(textureAtlas), bulletSystem(bulletSystem), bounds(bounds)
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

	auto beamFactory = std::make_shared<BeamFactory>(this->bounds, 0.5f);
	auto weaponComponent = std::make_shared<SingleBeamWeaponComponent>(bulletSystem, beamFactory, 5.0f, 1.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);

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
	auto texture = textureAtlas->GetTexture("playerExhaust");

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
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Green);
	auto movementComponent = std::make_shared<OffSetMovementComponent>(sf::Vector2f(-10.0, shipSpriteOrigin.y + 2));
	auto weaponComponent = std::make_shared<InertWeaponComponent>();
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto exhaust = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);
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
	auto texture = textureAtlas->GetTexture("playerTurret");

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
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Blue);
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(shipSpriteOrigin, 50.0f, 100.0f);
	auto projectileFactory = std::make_shared<ProjectileFactory>();
	auto weaponComponent = std::make_shared<SingleShotWeaponComponent>(bulletSystem, projectileFactory, 0.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto turret = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);
	auto sprite = turret->GetSprite();
	turret->SetTexture(texture);
	turret->InitAnimationComponent(texture);
	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	auto spriteBounds = sprite->getLocalBounds();
	//turret->InitHitboxComponent(
	//	spriteBounds.left - spriteFrameSize.x / 2,
	//	spriteBounds.top - spriteFrameSize.y / 2,
	//	spriteFrameSize.x,
	//	spriteFrameSize.y);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);

	turret->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	manifest["turret"] = turret;
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

	auto shipSpriteOrigin = manifest.at("ship")->GetSprite()->getOrigin();

	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>(sf::Color::Blue);
	auto movementComponent = std::make_shared<OrbitalMovementComponent>(shipSpriteOrigin, 75.0f, -100.0f);
	auto projectileFactory = std::make_shared<ProjectileFactory>();
	auto weaponComponent = std::make_shared<BurstShotWeaponComponent>(bulletSystem, projectileFactory, 10.0f, 360.0f, 50.0f);
	auto playerWeaponComponent = std::make_shared<PlayerWeaponComponent>(weaponComponent);
	auto glowie = std::make_shared<EntityObject>(animationComponent, hitboxComponent, movementComponent, playerWeaponComponent);
	auto sprite = glowie->GetSprite();
	glowie->SetTexture(texture);
	glowie->InitAnimationComponent(texture);
	sprite->setOrigin(spriteFrameSize.x / 2, spriteFrameSize.y / 2);
	sprite->setScale(sf::Vector2f(spriteScale, spriteScale));

	auto spriteBounds = sprite->getLocalBounds();
	//glowie->InitHitboxComponent(
	//	spriteBounds.left - spriteFrameSize.x / 2,
	//	spriteBounds.top - spriteFrameSize.y / 2,
	//	spriteFrameSize.x,
	//	spriteFrameSize.y);

	auto frameSize = sf::Vector2i(
		(int)spriteFrameSize.x,
		(int)spriteFrameSize.y);

	glowie->AddAnimation(this->IDLE, 0.05f, 0, 0, 3, 0, frameSize.x, frameSize.y);

	manifest["glowie"] = glowie;
}