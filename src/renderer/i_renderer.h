#ifndef I_RENDERER
#define I_RENDERER
#pragma once

#include <SFML/Graphics.hpp>

class IRenderer
{
public:
	IRenderer() = default;
	virtual ~IRenderer() = default;

	virtual void Draw(sf::RenderTarget& window) const = 0;
	virtual void Clear(sf::Color color = sf::Color::Transparent) const = 0;

	virtual sf::RenderTexture& GetTarget() const = 0;
	virtual sf::RenderTexture& GetDebugTarget() const = 0;

	virtual void AddGlow(sf::Vector2f position, sf::Color color, float attenuation) = 0;
};

#endif // I_RENDERER