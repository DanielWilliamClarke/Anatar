#include "space_level.h"

#include <stdlib.h>

SpaceLevel::SpaceLevel(std::shared_ptr<IRandomNumberSource<int>> randSource, sf::Vector2f viewSize)
	: randSource(randSource), viewSize(viewSize)
{
	auto starChartX = randSource->Generate(stars.size(), 0, (int)viewSize.x);
	auto starChartY = randSource->Generate(stars.size(), 0, (int)viewSize.y);

	for (auto i = 0; i < stars.size(); i++) {
		auto& s = stars[i];
		s = sf::CircleShape(0.75f);
		s.setFillColor(sf::Color::White);
		s.setPosition((float)starChartX[i], (float)starChartY[i]);
	}
}

void SpaceLevel::Update(float worldSpeed, float dt)
{
	for (auto i = 0; i < stars.size(); i++) {

		auto& s = stars[i];

		auto starPosition = s.getPosition();

		auto paralaxFactor = 1.0f;
		if (i < 300)
		{
			paralaxFactor = 0.5f;
			s.setFillColor(sf::Color(128, 128, 128));
		}
		else if (i < 350)
		{
			paralaxFactor = 0.7f;
			s.setFillColor(sf::Color(255, 215, 0));
			s.setRadius(1.0f);
		}
		else if (i < 375)
		{
			paralaxFactor = 1.1f;
			s.setFillColor(sf::Color(0, 255, 255));
			s.setRadius(1.5f);
		}

		starPosition.x -= worldSpeed * dt * paralaxFactor;

		if (starPosition.x < 0) 
		{
			starPosition.x = viewSize.x;
			starPosition.y = (float)randSource->Generate(0, (int)viewSize.y);
		}

		s.setPosition(starPosition);	
	}
}

void SpaceLevel::Draw(sf::RenderTarget& target, sf::Sprite& glowSprite, sf::Shader& shader) const
{
	for (auto &s : stars) {

		target.draw(s);

		if (s.getRadius() >= 1.5f)
		{
			auto color = s.getFillColor();
			shader.setUniform("frag_LightOrigin", s.getPosition());
			shader.setUniform("frag_LightColor", sf::Vector3f(color.r, color.g, color.b));
			shader.setUniform("frag_LightAttenuation", 500.0f);

			sf::RenderStates states;
			states.shader = &shader;
			states.blendMode = sf::BlendAdd;

			target.draw(glowSprite, states);
		}
	}
}