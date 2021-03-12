#ifndef ENTITY_H
#define ENTITY_H
#pragma once 

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class IRenderer;

class IEntityObjectBuilder;
class IGlobalMovementComponent;
class IAttributeComponent;

class EntityObject;
struct EntityUpdate;
struct BulletConfig;
struct RayIntersection;

template<typename U, typename C>
class QuadTree;

class Entity;
struct EntityCollision {
	std::shared_ptr<Entity> target;
	sf::Vector2f point;

	EntityCollision(std::shared_ptr<Entity> target, sf::Vector2f point = sf::Vector2f())
		: target(target), point(point)
	{}
};

typedef QuadTree<Entity, EntityCollision> CollisionQuadTree;
typedef std::map<std::string, std::shared_ptr<EntityObject>> EntityManifest;

class Entity: public std::enable_shared_from_this<Entity>
{
public:
	Entity() = default;
	Entity(
		std::shared_ptr<IEntityObjectBuilder> entityBuilder,
		std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
		std::shared_ptr<IAttributeComponent> attributeComponent,
		std::string tag);
	virtual ~Entity() = default;

	void AddObject(std::string name, std::shared_ptr<EntityObject> object);
	void RemoveObject(std::string name);
	std::shared_ptr<EntityObject> GetObject(std::string name) const;

	virtual void Update(std::shared_ptr<CollisionQuadTree> quadTree, float dt) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const = 0;
	virtual bool IsInside(sf::FloatRect& area) const = 0;
	virtual sf::Vector2f GetPosition() const = 0;


	bool DetectCollision(sf::Vector2f& position) const;
	std::shared_ptr<RayIntersection> DetectCollisionWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const;

	void TakeDamage(float damage, sf::Vector2f& impactPoint);
	void RegisterKill(float score);
	bool HasDied() const;

	std::string GetTag() const;

protected:
	void UpdateObjects(std::map<std::string, EntityUpdate> update, float dt) const;
	void DrawObjects(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const;

	EntityManifest objects;
	std::shared_ptr<IEntityObjectBuilder> entityBuilder;
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent;
	std::shared_ptr<IAttributeComponent> attributeComponent;

	std::map<std::string, std::shared_ptr<BulletConfig>> bulletConfigs;
	std::string tag;

private:

};

#endif //ENTITY_H