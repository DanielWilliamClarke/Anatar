#ifndef I_HITBOX_COMPONENT_H
#define I_HITBOX_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class IHitboxComponent
{
public:
	IHitboxComponent() = default;
	virtual ~IHitboxComponent() = default;

	virtual void SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height) = 0;
	virtual void Update() = 0;
	virtual void Draw(sf::RenderTarget& target) = 0;
	virtual bool Intersects(const sf::FloatRect& hitbox) = 0;
	virtual const bool IsRequired() const = 0;
};

#endif //I_HITBOX_COMPONENT_H