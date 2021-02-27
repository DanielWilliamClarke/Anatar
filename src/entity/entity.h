#ifndef ENTITY_H
#define ENTITY_H
#pragma once 

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class IEntityObjectBuilder;
class IGlobalMovementComponent;
class IAttributeComponent;

class EntityObject;
struct EntityUpdate;
struct BulletConfig;
struct RayIntersection;

typedef std::map<std::string, std::shared_ptr<EntityObject>> EntityManifest;

class Entity: public std::enable_shared_from_this<Entity>
{
public:
	Entity() = default;
	Entity(
		std::shared_ptr<IEntityObjectBuilder> entityBuilder,
		std::shared_ptr<IGlobalMovementComponent> globalMovementComponent,
		std::shared_ptr<IAttributeComponent> attributeComponent);
	virtual ~Entity() = default;

	void AddObject(std::string name, std::shared_ptr<EntityObject> object);
	void RemoveObject(std::string name);
	std::shared_ptr<EntityObject> GetObject(std::string name) const;

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderTarget& target, float interp) const = 0;
	virtual sf::Vector2f GetPosition() const;

	bool DetectCollision(sf::FloatRect hitbox) const;
	std::shared_ptr<RayIntersection> DetectCollisionWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const;

	void TakeDamage(float damage);
	void RegisterKill(float score);
	bool HasDied() const;

	float DistanceTo(sf::Vector2f position) const;

protected:
	void UpdateObjects(std::map<std::string, EntityUpdate> update, float dt) const;
	void DrawObjects(sf::RenderTarget& target, sf::Vector2f interPosition) const;

	EntityManifest objects;
	std::shared_ptr<IEntityObjectBuilder> entityBuilder;
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent;
	std::shared_ptr<IAttributeComponent> attributeComponent;

	std::map<std::string, std::shared_ptr<BulletConfig>> bulletConfigs;

private:

};

#endif //ENTITY_H