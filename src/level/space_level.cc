#include "space_level.h"

#include <stdlib.h>

#include "../util/i_random_number_source.h"

SpaceLevel::SpaceLevel(std::shared_ptr<IRandomNumberSource<int>> randSource, sf::Vector2f viewSize)
	: randSource(randSource), viewSize(viewSize)
{
	auto starChartX = randSource->Generate(stars.size(), 0, (int)viewSize.x);
	auto starChartY = randSource->Generate(stars.size(), 0, (int)viewSize.y);

	for (auto i = 0; i < stars.size(); i++) {
		auto& s = stars[i];
		s = sf::CircleShape(0.75);
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
			s.setRadius(1);
		}
		else if (i < 375)
		{
			paralaxFactor = 1.1f;
			s.setFillColor(sf::Color(0, 255, 255));
			s.setRadius(1.5);
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

void SpaceLevel::Draw(sf::RenderTarget& target) const
{
	for (auto &s : stars) {
		target.draw(s);
	}
}