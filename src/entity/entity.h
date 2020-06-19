#pragma once 
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class IEntityObjectBuilder;
class IGlobalMovementComponent;
class EntityObject;

struct Input;
struct EntityUpdate;

class Entity {

public:
	Entity() = default;
	Entity(
		std::shared_ptr<IEntityObjectBuilder> entityBuilder,
		std::shared_ptr<IGlobalMovementComponent> globalMovementComponent);
	virtual ~Entity() = default;

	void AddObject(std::string name, std::shared_ptr<EntityObject> object);
	std::shared_ptr<EntityObject> GetObject(std::string name);

	virtual void Update(Input in, float dt) const = 0;
	virtual void Draw(sf::RenderTarget& target, float interp) const = 0;

protected:
	void UpdateObjects(std::map<std::string, EntityUpdate> update, float dt) const;
	void DrawObjects(sf::RenderTarget& target, sf::Vector2f interPosition) const;

	std::map<std::string, std::shared_ptr<EntityObject>> objects;
	std::shared_ptr<IEntityObjectBuilder> entityBuilder;
	std::shared_ptr<IGlobalMovementComponent> globalMovementComponent;

private:

};