#include "fps.h"

Fps::Fps()
{
  font.loadFromFile("./assets/digital.ttf");
  fps.setFont(font);
  dps.setFont(font);
  fps.setPosition(2.0f, 0.0f);
  dps.setPosition(2.0f, 15.0f);
  //Set size
  fps.setScale(0.5, 0.5);
  dps.setScale(0.5, 0.5);
  // set the color
  fps.setFillColor(sf::Color::Cyan);
  dps.setFillColor(sf::Color::Cyan);
  frames = draws = -1;
}

void Fps::Update()
{
  if (clockUpdate.getElapsedTime().asSeconds() >= 1.0f)
  {
    fps.setString("FPS: " + std::to_string(frames));
    frames = 0;
    clockUpdate.restart();
  }
  frames++;
}

void Fps::Draw(sf::RenderTarget &window)
{
  if (clockDraw.getElapsedTime().asSeconds() >= 1.0f)
  {
    dps.setString("Draw Calls: " + std::to_string(draws));
    draws = 0;
    clockDraw.restart();
  }
  draws++;

  window.draw(fps);
  window.draw(dps);
}