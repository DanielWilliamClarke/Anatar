#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class AnimationComponent;
class MovementComponent;

class Player
{
public:
  Player(
	  std::shared_ptr<AnimationComponent> animationComponent,
	  std::shared_ptr<MovementComponent> movementComponent);
  void Update(float delta);
  void Draw(sf::RenderWindow &window, float interp);

private:
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<MovementComponent> movementComponent;
};
