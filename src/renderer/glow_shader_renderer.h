#ifndef GLOW_SHADER_RENDERER
#define GLOW_SHADER_RENDERER


#include <SFML/Graphics.hpp>

#include "i_glow_shader_renderer.h"

class GlowShaderRenderer: public IGlowShaderRenderer
{
public:
	GlowShaderRenderer(sf::Vector2f bounds);
	virtual ~GlowShaderRenderer() = default;
	virtual void Draw(sf::RenderTarget& window) const override;
	virtual sf::RenderTexture& ExposeTarget() const override;
	virtual void Clear(sf::Color color) const override;
	virtual void AddGlowAtPosition(sf::Vector2f position, sf::Color color, float attenuation) override;

private:

	sf::Shader shader;
	mutable sf::RenderTexture windowTexture;
	sf::Sprite glowSprite;

};

#endif // GLOW_SHADER_RENDERER