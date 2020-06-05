#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "animation_component.h"
#include "movement_component.h"
#include "config.h"
#include "player.h"
#include "fps.h"

int main(int argc, char *argv[])
{
  std::cout << "Version " << Anarion_VERSION_MAJOR << "." << Anarion_VERSION_MINOR << std::endl;

  sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Demo");

  auto view = renderWindow.getView();
  sf::Vector2i viewCenter(view.getCenter());
  sf::Vector2i viewSize(view.getSize());
  sf::FloatRect bounds(viewCenter.x - viewSize.x / 2, // left
                       viewCenter.y - viewSize.y / 2, // top
                       viewSize.x,
                       viewSize.y);

  std::cout
      << "View Bounds (left: "
      << std::to_string(bounds.left)
      << ", top: "
      << std::to_string(bounds.top)
      << ", width: "
      << std::to_string(bounds.width)
      << ", height: "
      << std::to_string(bounds.height)
      << ")"
      << std::endl;

  sf::Texture texture;
  texture.loadFromFile("./assets/pikaFrames.png");
  auto sprite = sf::Sprite(texture);
  sprite.setScale(sf::Vector2f(3.0f, 3.0f)); // absolute scale factor
  sprite.setPosition(renderWindow.getView().getCenter());

  auto animationComponent = std::make_shared<AnimationComponent>(sprite, texture);
  auto movementComponent = std::make_shared< MovementComponent>(sprite, bounds);

  Player pika(sprite, animationComponent, movementComponent);
  Fps fpsCounter;

  sf::Clock clock;
  auto dt = 1.0 / 60.0f;
  auto accumulator = 0.0f;
  while (renderWindow.isOpen())
  {
    sf::Event event;
    while (renderWindow.pollEvent(event))
      if (event.type == sf::Event::Closed)
        renderWindow.close();

    accumulator += clock.restart().asSeconds();
    while (accumulator >= dt)
    {
      pika.Update(dt);
      fpsCounter.Update();
      accumulator -= dt;
    }
    auto interp = accumulator / dt;

    renderWindow.clear(sf::Color(255, 255, 255, 255));

    pika.Draw(renderWindow, interp);
    fpsCounter.Draw(renderWindow);

    renderWindow.display();
  }
}
