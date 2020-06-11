#pragma once 
#include <memory>

namespace sf {
	class Sprite;
	class Texture;
	class RenderTarget;
}

class EntityComposition;
class MovementComponent;
struct Input;

class Entity {

public:
	Entity() = default;
	Entity(
		std::shared_ptr<EntityComposition> group,
		std::shared_ptr<MovementComponent> globalMovementComponent);
	virtual ~Entity() = default;

	virtual void Update(float dt) const = 0;
	virtual void Update(Input in, float dt) const = 0;
	virtual void Draw(sf::RenderTarget& target, float interp) const = 0;

protected:

	std::shared_ptr<EntityComposition> group;
	std::shared_ptr<MovementComponent> globalMovementComponent;
private:

};