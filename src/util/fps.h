#ifndef FPS_H
#define FPS_H
#pragma once

#include <SFML/Graphics.hpp>

class Fps
{
public:
  Fps();
  virtual ~Fps() = default;
  void Update();
  void Draw(sf::RenderWindow &window);

private:
  // Clocks
  sf::Clock clockUpdate;
  sf::Clock clockDraw;

  // Diag
  int frames;
  int draws;
  sf::Font font;
  sf::Text fps;
  sf::Text dps;
};

#endif //FPS_H