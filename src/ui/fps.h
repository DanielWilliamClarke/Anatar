#ifndef FPS_H
#define FPS_H


#include <SFML/Graphics.hpp>
#include <memory>

class IRenderer;

class Fps
{
public:
  Fps();
  virtual ~Fps() = default;
  void Update();
  void Draw(std::shared_ptr<IRenderer> renderer);

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