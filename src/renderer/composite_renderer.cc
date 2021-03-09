#include "composite_renderer.h"

#include "i_glow_shader_renderer.h"

CompositeRenderer::CompositeRenderer(std::shared_ptr<IGlowShaderRenderer> glowRenderer, sf::Vector2f bounds)
	: glowRenderer(glowRenderer)
{
	this->debugWindowTexture.create((int)bounds.x, (int)bounds.y);
}

void CompositeRenderer::Draw(sf::RenderTarget& window) const
{
	this->glowRenderer->Draw(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
	{
		this->debugWindowTexture.display();
		window.draw(sf::Sprite(this->debugWindowTexture.getTexture()));
	}
}

void CompositeRenderer::Clear(sf::Color color) const
{
	this->glowRenderer->Clear(color);
	this->debugWindowTexture.clear(color);
}

sf::RenderTexture& CompositeRenderer::GetTarget() const
{
	return this->glowRenderer->ExposeTarget();
}

sf::RenderTexture& CompositeRenderer::GetDebugTarget() const
{
	return this->debugWindowTexture;
}

void CompositeRenderer::AddGlow(sf::Vector2f position, sf::Color color, float attenuation)
{
	this->glowRenderer->AddGlowAtPosition(position, color, attenuation);
}
