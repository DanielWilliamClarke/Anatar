#include "entity.h"

#include "components/animation_component.h"
#include "components/movement_component.h"
#include "components/hitbox_component.h"

Entity::Entity(
	std::shared_ptr<AnimationComponent> animationComponent,
	std::shared_ptr<MovementComponent> movementComponent,
	std::shared_ptr<HitboxComponent> hitboxComponent)
	: animationComponent(animationComponent),
	movementComponent(movementComponent), 
	hitboxComponent(hitboxComponent),
	sprite(std::make_shared<sf::Sprite>())
{}

void Entity::SetTexture(std::shared_ptr<sf::Texture> texture) const
{
	this->sprite->setTexture(*texture);
}

void Entity::InitAnimationComponent(std::shared_ptr<sf::Texture> textureSheet) const
{
	this->animationComponent->SetAssets(this->sprite, textureSheet);
}

void Entity::InitMovementComponent() const
{
	this->movementComponent->SetSprite(this->sprite);
}

void Entity::InitHitboxComponent(float offsetX, float offsetY, float width, float height) const
{
	this->hitboxComponent->SetSprite(this->sprite, offsetX, offsetY, width, height);
}

