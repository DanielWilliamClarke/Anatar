#ifndef I_PLAYER_HUD
#define I_PLAYER_HUD
#pragma once

#include <SFML/Graphics.hpp>

class IPlayerHud
{
public:
	IPlayerHud() = default;
	virtual ~IPlayerHud() = default;

	virtual void Update(float health, float maxHealth, float shields, float maxShields, float score) = 0;
	virtual void Draw(sf::RenderTarget& target) const = 0;
};

#endif // I_PLAYER_HUD