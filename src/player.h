#pragma once
#include <memory>

namespace sf {
	class Sprite;
	class Texture;
	class RenderWindow;
}

class AnimationComponent;
class MovementComponent;
struct Input;

class Player
{
public:
  Player(
	  std::shared_ptr<AnimationComponent> animationComponent,
	  std::shared_ptr<MovementComponent> movementComponent);
  void Update(Input in, float delta);
  void Draw(sf::RenderWindow &window, float interp);

private:
	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<MovementComponent> movementComponent;
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> texture;
};
