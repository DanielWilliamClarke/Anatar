#ifndef ENTITY_H
#define ENTITY_H
#pragma once 

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <functional>

class IRenderer;

class IEntityObjectBuilder;
class IGlobalMovementComponent;
class IAttributeComponent;
class ICollisionDetectionComponent;

class EntityObject;
struct EntityUpdate;
struct BulletConfig;
struct RayIntersection;

struct Collision;
template<typename C>
class QuadTree;

using ObjectID = unsigned int;
using EntityManifest = std::map<ObjectID, std::shared_ptr<EntityObject>>;

class Entity: public std::enable_shared_from_this<Entity>
{
public:
	Entity() = default;
	Entity(
		std::shared_ptr<IEntityObjectBuilder> entityBuilder,
		std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
		std::shared_ptr<IAttributeComponent> attributeComponent,
		std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent,
		std::string tag);
	virtual ~Entity() = default;

	void AddObject(ObjectID id, std::shared_ptr<EntityObject> object);
	void RemoveObject(ObjectID id);
	std::shared_ptr<EntityObject> GetObject(ObjectID id) const;

	virtual void Update(std::shared_ptr<QuadTree<Collision>> quadTree, float dt) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const = 0;
	virtual sf::Vector2f GetPosition() const = 0;

	std::shared_ptr<sf::Vector2f> DetectCollision(const sf::Vector2f& origin, const bool ray = false, const sf::Vector2f& direction = sf::Vector2f()) const;

	void TakeDamage(float damage, sf::Vector2f& impactPoint);
	void RegisterKill(float score);
	bool HasDied() const;

	std::string GetTag() const;

protected:
	void UpdateObjects(std::map<ObjectID, EntityUpdate> update, float dt) const;
	void DrawObjects(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const;

	EntityManifest objects;
	std::shared_ptr<IEntityObjectBuilder> entityBuilder;
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent;
	std::shared_ptr<IAttributeComponent> attributeComponent;
	std::shared_ptr<ICollisionDetectionComponent> collisionDetectionComponent;

	std::map<ObjectID, std::shared_ptr<BulletConfig>> bulletConfigs;
	std::string tag;

private:

};

#endif //ENTITY_H