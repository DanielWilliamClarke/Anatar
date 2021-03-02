#include "space_level.h"

#include <thread>

#include "util/i_glow_shader_renderer.h"
#include "util/i_threaded_workload.h"

SpaceLevel::SpaceLevel(std::shared_ptr<IThreadedWorkload> threadableWorkload, std::shared_ptr<IRandomNumberSource<int>> randSource, sf::Vector2f viewSize)
	: threadableWorkload(threadableWorkload), randSource(randSource), viewSize(viewSize), totalStars(200)
{
	auto starChartX = randSource->Generate(totalStars, 0, (int)viewSize.x);
	auto starChartY = randSource->Generate(totalStars, 0, (int)viewSize.y);

	stars.reserve(totalStars);
	for (auto i = 0; i < totalStars; i++)
	{
		auto s = sf::CircleShape(0.75f, 3);
		s.setFillColor(sf::Color::White);
		s.setPosition((float)starChartX[i], (float)starChartY[i]);
		auto bounds = s.getLocalBounds();
		s.setOrigin(bounds.width / 2, bounds.height / 2);
		stars.emplace_back(std::make_unique<sf::CircleShape>(s));
	}
}

void SpaceLevel::Update(float worldSpeed, float dt)
{
	auto chunkSize = stars.size() / 2;
	this->threadableWorkload->Reserve(chunkSize);
	for (size_t index = 0; index < stars.size(); index += chunkSize)
	{
		auto start = stars.begin() + index;
		auto end = stars.begin() + std::min(stars.size(), index + chunkSize);
		this->threadableWorkload
			->AddThread(std::thread(
				[&](StarIter start, StarIter end, int index) {
					this->UpdateStars(start, end, index, worldSpeed, dt);
				}, start, end, index));
	}
	this->threadableWorkload->Join();
}

void SpaceLevel::Draw(std::shared_ptr<IGlowShaderRenderer> renderer) const
{
	for (auto& s : stars)
	{
		renderer->ExposeTarget().draw(*s);
		if (s->getRadius() >= 1.5f)
		{
			renderer->AddGlowAtPosition(s->getPosition(), s->getFillColor(), 500.0f);
		}
	}
}

void SpaceLevel::UpdateStars(StarIter start, StarIter end, int index, float worldSpeed, float dt) const
{
	auto totalStars = stars.size();
	for (auto iter = start; iter != end; iter++)
	{
		auto& s = (*iter);
		auto starPosition = s->getPosition();
		auto paralaxFactor = 1.0f;

		if (index < totalStars * 0.8)
		{
			paralaxFactor = 0.5f;
			s->setFillColor(sf::Color(128, 128, 128));
		}
		else if (index < totalStars * 0.85)
		{
			paralaxFactor = 0.7f;
			s->setFillColor(sf::Color(255, 215, 0));
			s->setRadius(1.0f);
		}
		else if (index < totalStars * 0.9)
		{
			paralaxFactor = 1.1f;
			s->setFillColor(sf::Color(0, 255, 255));
			s->setRadius(1.5f);
		}
		else if (index < totalStars * 0.95)
		{
			paralaxFactor = 0.5f;
			s->setFillColor(sf::Color(255, 0, 0));
			s->setRadius(0.7f);
		}

		starPosition.x -= worldSpeed * dt * paralaxFactor;
		if (starPosition.x < 0)
		{
			starPosition.x = viewSize.x;
			starPosition.y = (float)randSource->Generate(0, (int)viewSize.y);
		}

		s->setPosition(starPosition);
		index++;
	}
}