#include "entity_object.h"

#include "components/animation/i_animation_component.h"
#include "components/hitbox/i_hitbox_component.h"
#include "components/movement/i_local_movement_component.h"
#include "components/weapon/i_weapon_component.h"

EntityObject::EntityObject(
	std::shared_ptr<IAnimationComponent> animationComponent,
	std::shared_ptr<IHitboxComponent> hitboxComponent,
	std::shared_ptr<ILocalMovementComponent> movementComponent,
	std::shared_ptr<IWeaponComponent> weaponComponent)
	: animationComponent(animationComponent),
	hitboxComponent(hitboxComponent),
	movementComponent(movementComponent),
	weaponComponent(weaponComponent),
	sprite(std::make_shared<sf::Sprite>())
{
}

void EntityObject::SetTexture(std::shared_ptr<sf::Texture> texture) const
{
	this->sprite->setTexture(*texture);
}

void EntityObject::InitAnimationComponent(std::shared_ptr<sf::Texture> textureSheet)
{
	this->animationComponent->SetAssets(this->sprite, textureSheet);
}

void EntityObject::InitHitboxComponent(float offsetX, float offsetY, float width, float height)
{
	this->hitboxComponent->SetSprite(this->sprite, offsetX, offsetY, width, height);
}

void EntityObject::AddAnimation(const int key, float frameDuration,
	int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	this->animationComponent->AddAnimation(key, frameDuration, startFrameX, startFrameY, framesX, framesY, width, height);
}

void EntityObject::PlayAnimation(const int direction, const bool loop) const
{
	this->animationComponent->Play(direction, loop);
}

std::shared_ptr<sf::Sprite> EntityObject::GetSprite() const 
{
	return this->sprite;
}

void EntityObject::Update(EntityUpdate update, float dt) const
{
	this->sprite->setPosition(this->movementComponent->Integrate(update.position, dt));

	if (update.fire) 
	{
		this->weaponComponent->Fire(this->sprite->getPosition(), update.bulletConfig);
	}

	this->animationComponent->Play(update.direction, update.loop);
	if (this->hitboxComponent->IsRequired()) {
		this->hitboxComponent->Update();
	}
}

void EntityObject::Draw(sf::RenderTarget& target, sf::Vector2f interPosition) const
{
	this->sprite->setPosition(this->movementComponent->Interpolate(interPosition));
	target.draw(*this->sprite);
	if (this->hitboxComponent->IsRequired())
	{
		this->hitboxComponent->Update();
		this->hitboxComponent->Draw(target);
	}
}

bool EntityObject::DetectCollision(sf::Vector2f& position) const
{
	return this->hitboxComponent->Contains(position);
}

std::shared_ptr<RayIntersection> EntityObject::DetectCollisionWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const
{
	return this->hitboxComponent->IntersectsWithRay(origin, direction);
}