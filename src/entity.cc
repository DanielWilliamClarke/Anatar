#include "entity.h"

#include "animation_component.h"
#include "movement_component.h"

Entity::Entity(
	std::shared_ptr<AnimationComponent> animationComponent,
	std::shared_ptr<MovementComponent> movementComponent)
	: animationComponent(animationComponent),
	movementComponent(movementComponent), 
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

