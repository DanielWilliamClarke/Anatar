#pragma once 
#include <memory>

namespace sf {
	class Sprite;
	class Texture;
	class RenderTarget;
}

class AnimationComponent;
class MovementComponent;
struct Input;

class Entity {

public:
	Entity() = default;
	Entity(
		std::shared_ptr<AnimationComponent> animationComponent,
		std::shared_ptr<MovementComponent> movementComponent);
	virtual ~Entity() = default;

	virtual void Update(float dt) const = 0;
	virtual void Update(Input in, float dt) const = 0;
	virtual void Draw(sf::RenderTarget& target, float interp) const = 0;

protected:
	void SetTexture(std::shared_ptr<sf::Texture> texture) const;
	void InitAnimationComponent(std::shared_ptr<sf::Texture> textureSheet) const;
	void InitMovementComponent() const;

	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<MovementComponent> movementComponent;

private:

};