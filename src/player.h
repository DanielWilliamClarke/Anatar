#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class AnimationComponent;
class MovementComponent;

class Player
{
public:
  Player(
	  sf::Sprite& sprite,
	  std::shared_ptr<AnimationComponent> animationComponent,
	  std::shared_ptr<MovementComponent> movementComponent);
  void Update(float delta);
  void Draw(sf::RenderWindow &window, float interp);

private:
	sf::Sprite& sprite;
	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<MovementComponent> movementComponent;
};
