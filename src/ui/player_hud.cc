#include "player_hud.h"

#include "renderer/i_renderer.h"

PlayerHud::PlayerHud(sf::FloatRect bounds)
	: bounds(bounds), margin(10.f)
{
	font.loadFromFile("./assets/EightBitDragon-anqx.ttf");

	playerText.setFont(font);
	playerText.setCharacterSize(15);
	scoreText.setFont(font);
	scoreText.setCharacterSize(15);

	auto barMaxWidth = bounds.width - (margin * 2);

	healthBar.setSize(sf::Vector2f(barMaxWidth, 15.0f));
	auto healthBarBounds = healthBar.getLocalBounds();
	healthBar.setPosition(margin, bounds.height - healthBarBounds.height - margin);

	shieldBar.setSize(sf::Vector2f(barMaxWidth, 10.0f));
	auto shieldBarBounds = shieldBar.getLocalBounds();
	shieldBar.setPosition(margin, bounds.height - shieldBarBounds.height - margin * 2.5f);
}

void PlayerHud::Update(float health, float maxHealth, float shields, float maxShields, float score)
{
	auto barMaxWidth = bounds.width - (margin * 2);

	auto healthPercentage = health / maxHealth;
	healthBar.setSize(sf::Vector2f(barMaxWidth * healthPercentage, 15.0f));
	if (healthPercentage > 0.5f)
	{
		healthBar.setFillColor(BlendColor(sf::Color(130, 190, 60), sf::Color::Yellow, (healthPercentage - 0.5f) / (1.0f - 0.5f)));
	}
	else
	{
		healthBar.setFillColor(BlendColor(sf::Color::Yellow, sf::Color::Red, (healthPercentage - 0.0f) / (0.5f - 0.0f)));
	}

	auto shieldPercentage = shields / maxShields;
	shieldBar.setSize(sf::Vector2f(barMaxWidth * shieldPercentage, 10.0f));
	if (shieldPercentage > 0.5f)
	{
		shieldBar.setFillColor(BlendColor(sf::Color::Cyan, sf::Color(8, 146, 208), (shieldPercentage - 0.5f) / (1.0f - 0.5f)));
	}
	else
	{
		shieldBar.setFillColor(BlendColor(sf::Color(8, 146, 208), sf::Color::Red, (shieldPercentage - 0.0f) / (0.5f - 0.0f)));
	}

	playerText.setString("Health: " + std::to_string((int)health) + " - Shields: " + std::to_string((int)shields));
	auto playerBounds = playerText.getLocalBounds();
	auto textHeight = bounds.height - playerBounds.height - margin * 4.0f;
	playerText.setPosition(margin, textHeight);

	scoreText.setString("Score: " + std::to_string((int)score));
	auto scoreBounds = scoreText.getLocalBounds();
	scoreText.setPosition(bounds.width - scoreBounds.width - margin, textHeight);
}

void PlayerHud::Draw(const std::shared_ptr<IRenderer>& renderer) const
{
	renderer->GetTarget().draw(playerText);
	renderer->GetTarget().draw(scoreText);
	renderer->GetTarget().draw(healthBar);
	renderer->GetTarget().draw(shieldBar);
}

sf::Color PlayerHud::BlendColor(const sf::Color& start, const sf::Color& end, float percentage)
{
	return {
		(sf::Uint8)((start.r - end.r) * percentage + end.r),
		(sf::Uint8)((start.g - end.g) * percentage + end.g),
		(sf::Uint8)((start.b - end.b) * percentage + end.b)
    };
}