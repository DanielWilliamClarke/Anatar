#include "glow_shader_renderer.h"

static const std::string shaderCode = \
"uniform vec2 frag_LightOrigin;"\
"uniform vec3 frag_LightColor;"\
"uniform float frag_LightAttenuation;"\
"uniform vec2 frag_ScreenResolution;"\
"void main(){"\
" vec2 baseDistance =  gl_FragCoord.xy;"\
" baseDistance.y = frag_ScreenResolution.y-baseDistance.y;"\
" vec2 distance=frag_LightOrigin - baseDistance;"\
" float linear_distance = length(distance);"\
" float attenuation=1.0/( frag_LightAttenuation*linear_distance + frag_LightAttenuation*linear_distance);"\
" vec4 lightColor = vec4(frag_LightColor,  clamp(frag_LightAttenuation, 0.0 ,frag_LightAttenuation));"\
" vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor; gl_FragColor=color;}";

GlowShaderRenderer::GlowShaderRenderer(sf::Vector2f bounds)
{
	this->windowTexture.create((int)bounds.x, (int)bounds.y);
    this->glowSprite.setTexture(this->windowTexture.getTexture());
    this->glowSprite.setOrigin((float)this->glowSprite.getTextureRect().width / 2, (float)this->glowSprite.getTextureRect().height / 2);
    this->glowSprite.setPosition(bounds.x / 2.f, bounds.y / 2.f);

    this->shader.loadFromMemory(shaderCode, sf::Shader::Fragment);
    this->shader.setUniform("frag_ScreenResolution", bounds);
}

void GlowShaderRenderer::Clear() const
{
    this->windowTexture.clear(sf::Color::Transparent);
}

void GlowShaderRenderer::Draw(sf::RenderTarget& window) const
{
    this->windowTexture.display();
    window.draw(this->glowSprite);
}

sf::RenderTexture& GlowShaderRenderer::ExposeTarget() const 
{
    return this->windowTexture;
}

void GlowShaderRenderer::AddGlowAtPosition(sf::Vector2f position, sf::Color color, float attenuation)
{
    this->shader.setUniform("frag_LightOrigin", position);
    this->shader.setUniform("frag_LightColor", sf::Vector3f(color.r, color.g, color.b));
    this->shader.setUniform("frag_LightAttenuation", attenuation);

    sf::RenderStates states;
    states.shader = &shader;
    states.blendMode = sf::BlendAdd;

    this->windowTexture.draw(glowSprite, states);
}