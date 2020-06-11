#include "entity_object.h"

#include "../factories/i_animation_component_factory.h"
#include "../components/animation_component.h"
#include "../factories/i_hitbox_component_factory.h"
#include "../components/hitbox_component.h"

EntityObject::EntityObject(
	std::shared_ptr<IAnimationComponentFactory> animationComponentFactory,
	std::shared_ptr<IHitboxComponentFactory> hitboxComponentFactory) 
	: animationComponentFactory(animationComponentFactory),
	hitboxComponentFactory(hitboxComponentFactory),
	positionOffset(sf::Vector2f(.0f, .0f)),
	sprite(std::make_shared<sf::Sprite>())
{
}

void EntityObject::SetPositionOffect(sf::Vector2f offset)
{
	this->positionOffset = offset;
}

void EntityObject::SetTexture(std::shared_ptr<sf::Texture> texture) const
{
	this->sprite->setTexture(*texture);
}

void EntityObject::InitAnimationComponent(std::shared_ptr<sf::Texture> textureSheet)
{
	this->animationComponent = this->animationComponentFactory->CreateInstance();
	this->animationComponent->SetAssets(this->sprite, textureSheet);
}

void EntityObject::InitHitboxComponent(float offsetX, float offsetY, float width, float height)
{
	this->hitboxComponent = hitboxComponentFactory->CreateInstance();
	this->hitboxComponent->SetSprite(this->sprite, offsetX, offsetY, width, height);
}

void EntityObject::AddAnimation(const int key, float frameDuration,
	int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	this->animationComponent->AddAnimation(key, frameDuration, startFrameX, startFrameY, framesX, framesY, width, height);
}

std::shared_ptr<sf::Sprite> EntityObject::GetSprite() const 
{
	return this->sprite;
}

void EntityObject::Update(EntityUpdate update, float dt) const
{
	this->sprite->setPosition(update.newPosition + positionOffset);
	this->animationComponent->Play(update.direction, false);
	if (this->hitboxComponent) {
		this->hitboxComponent->Update();
	}
}

void EntityObject::Draw(sf::RenderTarget& target, sf::Vector2f interPosition) const
{
	this->sprite->setPosition(interPosition + positionOffset);
	target.draw(*this->sprite);
	if (this->hitboxComponent) {
		this->hitboxComponent->Update();
		this->hitboxComponent->Draw(target);
	}
}
