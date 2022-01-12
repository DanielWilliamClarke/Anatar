#ifndef ENTITY_H
#define ENTITY_H
#pragma once 

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <functional>

#include "entity_object.h"
#include "entity_update.h"
#include "components/movement/i_global_movement_component.h"
#include "components/attributes/i_attribute_component.h"
#include "components/collision_detection/i_collision_detection_component.h"
#include "quad_tree/quad_tree.h"
#include "bullet/collision.h"

template <typename C, typename P>
class QuadTree;

template<typename T>
class Entity: public std::enable_shared_from_this<Entity<T>>
{
public:
	Entity() = default;
	Entity(
		std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
		std::shared_ptr<IAttributeComponent> attributeComponent,
		std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent,
		std::string tag);
	virtual ~Entity() = default;

	void AddObject(T id, std::shared_ptr<EntityObject> object);
	void RemoveObject(T id);
	std::shared_ptr<EntityObject> GetObject(T id) const;

	virtual void Update(std::shared_ptr<QuadTree<Collision, CollisionMediators>> quadTree, float dt) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const = 0;

	std::shared_ptr<sf::Vector2f> DetectCollision(const sf::Vector2f& origin, const bool ray = false, const sf::Vector2f& direction = sf::Vector2f()) const;
	bool HasDied() const;

	std::string GetTag() const;

protected:
	void UpdateObjects(std::map<T, EntityUpdate> update, float dt) const;
	void DrawObjects(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const;

	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent;
	std::shared_ptr<IAttributeComponent> attributeComponent;
	std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent;

	std::map<T, std::shared_ptr<EntityObject>> objects;
	std::map<T, std::shared_ptr<BulletConfig>> bulletConfigs;

	std::string tag;
};

template <typename T>
Entity<T>::Entity(
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
	std::shared_ptr<IAttributeComponent> attributeComponent,
	std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent,
	std::string tag)
	: globalMovementComponent(globalMovementComponent), attributeComponent(attributeComponent), collisionDetectionComponent(collisionDetectionComponent), tag(tag)
{}

template <typename T>
void Entity<T>::AddObject(T id, std::shared_ptr<EntityObject> object)
{
	this->objects[id] = object;
}

template <typename T>
void Entity<T>::RemoveObject(T id)
{
	this->objects.erase(id);
}

template <typename T>
std::shared_ptr<EntityObject> Entity<T>::GetObject(T id) const
{
	return this->objects.at(id);
}

template <typename T>
void Entity<T>::UpdateObjects(std::map<T, EntityUpdate> update, float dt) const
{
	for (auto& up : update)
	{
		if (this->objects.count(up.first))
		{
			this->objects.at(up.first)->Update(up.second, dt);
		}
	}
}

template <typename T>
void Entity<T>::DrawObjects(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const
{
	for (auto& obj : this->objects)
	{
		obj.second->Draw(renderer, interPosition);
	}
}

template <typename T>
std::shared_ptr<sf::Vector2f> Entity<T>::DetectCollision(const sf::Vector2f& origin, const bool ray, const sf::Vector2f& direction) const
{
	for (auto& o : objects)
	{
		auto collision = this->collisionDetectionComponent->DetectCollision(o.second->GetHitbox(), origin, ray, direction);
		if (collision) {
			return collision;
		}
	}

	return nullptr;
}

template <typename T>
bool Entity<T>::HasDied() const
{
	return this->attributeComponent->IsDead();
}

template <typename T>
std::string Entity<T>::GetTag() const
{
	return tag;
}

#endif //ENTITY_H