#ifndef PLAYER_HUD
#define PLAYER_HUD
#pragma once

#include <SFML/Graphics.hpp>

#include "i_player_hud.h"

class PlayerHud : public IPlayerHud
{
public:
	PlayerHud(sf::FloatRect bounds);
	virtual ~PlayerHud() = default;

	virtual void Update(float health, float maxHealth, float shields, float maxShields, float score) override;
	virtual void Draw(sf::RenderTarget& target) const override;

private:

	sf::Color BlendColor(sf::Color start, sf::Color end, float percentage) const;

	sf::FloatRect bounds;
	float margin;

	sf::Font font;
	sf::Text scoreText;
	sf::Text playerText;

	sf::RectangleShape healthBar;
	sf::RectangleShape shieldBar;
};

#endif // PLAYER_HUD