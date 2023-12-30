#ifndef I_GLOW_SHADER_RENDERER
#define I_GLOW_SHADER_RENDERER


#include <SFML/Graphics.hpp>

class IGlowShaderRenderer
{
public:
	IGlowShaderRenderer() = default;
	virtual ~IGlowShaderRenderer() = default;
	virtual void Draw(sf::RenderTarget& window) const = 0;
	virtual sf::RenderTexture& ExposeTarget() const = 0;
	virtual void Clear(sf::Color color) const = 0;
	virtual void AddGlowAtPosition(sf::Vector2f position, sf::Color color, float attenuation) = 0;
};

#endif // I_GLOW_SHADER_RENDERER