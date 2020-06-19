#include <SFML/Graphics.hpp>

#include "entity.h"

#include "entity_object.h"
#include "entity_update.h"
#include "../components/i_global_movement_component.h"

Entity::Entity(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent)
	: entityBuilder(entityBuilder), globalMovementComponent(globalMovementComponent)
{}

void Entity::AddObject(std::string name, std::shared_ptr<EntityObject> object)
{
	this->objects[name] = object;
}

std::shared_ptr<EntityObject> Entity::GetObject(std::string name)
{
	return this->objects[name];
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