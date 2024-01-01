#include "entity_object.h"

#include "components/animation/i_animation_component.h"
#include "components/hitbox/i_hitbox_component.h"
#include "components/movement/i_local_movement_component.h"
#include "components/weapon/i_weapon_component.h"
#include "player/player_input.h"

#include "renderer/i_renderer.h"

EntityObject::EntityObject(
	std::shared_ptr<IAnimationComponent> animationComponent,
	std::shared_ptr<IHitboxComponent> hitboxComponent,
	std::shared_ptr<ILocalMovementComponent> movementComponent,
	std::shared_ptr<IWeaponComponent> weaponComponent,
	std::shared_ptr<sf::Sprite> sprite
)
	: animationComponent(animationComponent),
	hitboxComponent(hitboxComponent),
	movementComponent(movementComponent),
	weaponComponent(weaponComponent),
	sprite(sprite)
{}

EntityObject::~EntityObject() 
{
	this->weaponComponent->Cease();
}

void EntityObject::Update(EntityUpdate update, float dt) const
{
	this->sprite->setPosition(this->movementComponent->Integrate(update.position, dt));
    auto slot = this->weaponComponent->getSlot();

    if (
        update.weaponState.fire &&
        update.weaponState.triggers.contains(slot) &&
        update.weaponState.triggers.at(slot)
    )
	{
		this->weaponComponent->Fire(this->sprite->getPosition(), update.bulletConfig);
	}

	this->animationComponent->Play(update.direction, update.loop);
	this->hitboxComponent->Update(this->sprite->getPosition());
}

void EntityObject::Draw(const std::shared_ptr<IRenderer>& renderer, sf::Vector2f interPosition) const
{
	this->sprite->setPosition(this->movementComponent->Interpolate(interPosition));
	renderer->GetTarget().draw(*this->sprite);
	this->hitboxComponent->Update(this->sprite->getPosition());
	this->hitboxComponent->Draw(renderer);
}

std::shared_ptr<sf::Sprite> EntityObject::GetSprite() const
{
	return this->sprite;
}

sf::FloatRect EntityObject::GetHitbox() const
{
	return this->hitboxComponent->Get();
}