#ifndef GLOW_SHADER_RENDERER
#define GLOW_SHADER_RENDERER

#include <SFML/Graphics.hpp>

#include "i_glow_shader_renderer.h"

class GlowShaderRenderer: public IGlowShaderRenderer
{
public:
	explicit GlowShaderRenderer(sf::Vector2f bounds);
	~GlowShaderRenderer() override = default;
	void Draw(sf::RenderTarget& window) const override;
	sf::RenderTexture& ExposeTarget() const override;
	void Clear(sf::Color color) const override;
	void AddGlowAtPosition(sf::Vector2f position, sf::Color color, float attenuation) override;

private:

	sf::Shader shader;
	mutable sf::RenderTexture windowTexture;
	sf::Sprite glowSprite;

};

#endif // GLOW_SHADER_RENDERER