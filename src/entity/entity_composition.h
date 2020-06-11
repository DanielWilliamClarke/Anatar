#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
#include <map>
#include <string>

#include "entity_update.h"

class IAnimationComponentFactory;
class IHitboxComponentFactory;
class EntityObject;

class EntityComposition
{
public: 

	EntityComposition(
		std::shared_ptr<IAnimationComponentFactory> animationComponentFactory,
		std::shared_ptr<IHitboxComponentFactory> hitboxComponentFactory);
	virtual ~EntityComposition() = default;

	std::shared_ptr<EntityObject> AddAttachment(std::string name);
	std::shared_ptr<EntityObject> GetObject(std::string name);

	void Update(EntityUpdate update, float dt) const;
	void Draw(sf::RenderTarget& target, sf::Vector2f interpPosition) const;

private:
	std::map<std::string, std::shared_ptr<EntityObject>> objects;
	std::shared_ptr<IAnimationComponentFactory> animationComponentFactory;
	std::shared_ptr<IHitboxComponentFactory> hitboxComponentFactory;
};