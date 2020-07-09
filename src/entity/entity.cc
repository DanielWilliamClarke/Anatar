#include <SFML/Graphics.hpp>

#include "entity.h"

#include "entity_object.h"
#include "entity_update.h"
#include "../components/movement/i_global_movement_component.h"
#include "components/attributes/i_attribute_component.h"

Entity::Entity(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
	std::shared_ptr<IAttributeComponent> attributeComponent)
	: entityBuilder(entityBuilder), globalMovementComponent(globalMovementComponent), attributeComponent(attributeComponent)
{}

void Entity::AddObject(std::string name, std::shared_ptr<EntityObject> object)
{
	this->objects[name] = object;
}

void Entity::RemoveObject(std::string name)
{
	this->objects.erase(name);
}

std::shared_ptr<EntityObject> Entity::GetObject(std::string name) const
{
	return this->objects.at(name);
}

void Entity::UpdateObjects(std::map<std::string, EntityUpdate> update, float dt) const
{
	for (auto& up : update)
	{
		if (this->objects.count(up.first))
		{
			this->objects.at(up.first)->Update(up.second, dt);
		}
	}
}

void Entity::DrawObjects(sf::RenderTarget& target, sf::Vector2f interPosition) const
{
	for (auto& obj : this->objects)
	{
		obj.second->Draw(target, interPosition);
	}
}

bool Entity::DetectCollision(sf::FloatRect hitbox) const
{
	for (auto& o : objects)
	{
		if (o.second->DetectCollision(hitbox))
		{
			return true;
		}
	}

	return false;
}

void Entity::TakeDamage(float damage)
{
	this->attributeComponent->TakeDamage(damage);
}

bool Entity::HasDied() const
{
	return this->attributeComponent->IsDead();
}

void Entity::RegisterKill(float score)
{
	this->attributeComponent->RegisterKill(score);
}