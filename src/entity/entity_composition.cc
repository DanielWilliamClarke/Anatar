#include <SFML/Graphics.hpp>

#include "entity_composition.h"

#include "../factories/i_animation_component_factory.h"
#include "../factories/i_hitbox_component_factory.h"
#include "entity_object.h"
#include "entity_update.h"

EntityComposition::EntityComposition(
	std::shared_ptr<IAnimationComponentFactory> animationComponentFactory,
	std::shared_ptr<IHitboxComponentFactory> hitboxComponentFactory)
	: animationComponentFactory(animationComponentFactory),
	hitboxComponentFactory(hitboxComponentFactory)
{
}

std::shared_ptr<EntityObject> EntityComposition::AddAttachment(std::string name)
{
	auto object = std::make_shared<EntityObject>(animationComponentFactory, hitboxComponentFactory);

	this->objects[name] = object;

	return object;
}

std::shared_ptr<EntityObject> EntityComposition::GetObject(std::string name)
{
	return this->objects[name];
}

void EntityComposition::Update(EntityUpdate update, float dt) const
{
	for (auto& obj : this->objects)
	{
		obj.second->Update(update, dt);
	}
}

void EntityComposition::Draw(sf::RenderTarget& target, sf::Vector2f interpPosition) const
{
	for (auto& obj : this->objects)
	{
		obj.second->Draw(target, interpPosition);
	}
}