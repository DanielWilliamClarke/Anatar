#include <SFML/Graphics.hpp>
#include <math.h>

#include "entity.h"

#include "entity_object.h"
#include "entity_update.h"
#include "components/movement/i_global_movement_component.h"
#include "components/attributes/i_attribute_component.h"
#include "util/i_ray_caster.h"
#include "util/math_utils.h"
#include "quad_tree/quad_tree.h"

Entity::Entity(
	std::shared_ptr<IEntityObjectBuilder> entityBuilder,
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
	std::shared_ptr<IAttributeComponent> attributeComponent,
	std::string tag)
	: entityBuilder(entityBuilder), globalMovementComponent(globalMovementComponent), attributeComponent(attributeComponent), tag(tag)
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

void Entity::DrawObjects(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const
{
	for (auto& obj : this->objects)
	{
		obj.second->Draw(renderer, interPosition);
	}
}

bool Entity::DetectCollision(sf::Vector2f& position) const
{
	for (auto& o : objects)
	{
		if (o.second->DetectCollision(position))
		{
			return true;
		}
	}

	return false;
}

std::shared_ptr<RayIntersection> Entity::DetectCollisionWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const
{
	for (auto& o : objects)
	{
		auto intersection = o.second->DetectCollisionWithRay(origin, direction);
		if (intersection->intersects)
		{
			return intersection;
		}
	}

	return std::make_shared< RayIntersection>(false);
}


void Entity::TakeDamage(float damage, sf::Vector2f& impactPoint)
{
	this->attributeComponent->TakeDamage(damage, impactPoint);
}

bool Entity::HasDied() const
{
	return this->attributeComponent->IsDead();
}

void Entity::RegisterKill(float score)
{
	this->attributeComponent->RegisterKill(score);
}

std::string Entity::GetTag() const
{
	return tag;
}