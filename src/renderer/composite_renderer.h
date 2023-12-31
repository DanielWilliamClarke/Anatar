#ifndef COMPOSITE_RENDERER
#define COMPOSITE_RENDERER


#include <SFML/Graphics.hpp>

#include <memory>

#include "i_renderer.h"

class IGlowShaderRenderer;

class CompositeRenderer : public IRenderer
{
public:
	explicit CompositeRenderer(std::shared_ptr<IGlowShaderRenderer> glowRenderer, sf::Vector2f bounds);
	~CompositeRenderer() override = default;

	virtual void Draw(sf::RenderTarget& window) const override;
	virtual void Clear(sf::Color color = sf::Color::Transparent) const override;

	sf::RenderTexture& GetTarget() const override;
	sf::RenderTexture& GetDebugTarget() const override;
	void AddGlow(sf::Vector2f position, sf::Color color, float attenuation) override;

private: 
	mutable sf::RenderTexture windowTexture;
	mutable sf::RenderTexture debugWindowTexture;
	std::shared_ptr<IGlowShaderRenderer> glowRenderer;
};

#endif // COMPOSITE_RENDERER