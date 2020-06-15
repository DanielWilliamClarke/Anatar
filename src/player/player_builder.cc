#include <SFML/Graphics.hpp>

#include "player_builder.h"

#include "../components/animation_component.h"
#include "../components/movement_component.h"
#include "../components/hitbox_component.h"
#include "../entity/entity_object.h"

PlayerBuilder::PlayerBuilder(std::shared_ptr<MovementComponent> movementComponent)
	: Player{}
{}

EntityManifest PlayerBuilder::Build() const
{
	EntityManifest manifest;

	manifest["ship"] = this->BuildShip();

	return manifest;
}

std::shared_ptr<EntityObject> PlayerBuilder::BuildShip() const
{
	auto animationComponent = std::make_shared<AnimationComponent>();
	auto hitboxComponent = std::make_shared<HitboxComponent>();

	auto ship = std::make_shared<EntityObject>(animationComponent, hitboxComponent);
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

