#ifndef I_PLAYER_HUD
#define I_PLAYER_HUD
#pragma once

#include <SFML/Graphics.hpp>

class IRenderer;

class IPlayerHud
{
public:
	IPlayerHud() = default;
	virtual ~IPlayerHud() = default;

	virtual void Update(float health, float maxHealth, float shields, float maxShields, float score) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer) const = 0;
};

#endif // I_PLAYER_HUD