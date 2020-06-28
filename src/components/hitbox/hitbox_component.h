#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#pragma once
#include <memory>

#include "i_hitbox_component.h"

class HitboxComponent: public IHitboxComponent
{
public: 
	HitboxComponent(sf::Color colour);
	virtual ~HitboxComponent() = default;

	virtual void SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height) override;
	virtual void Update() override;
	virtual void Draw(sf::RenderTarget& target) override;
	virtual bool Intersects(const sf::FloatRect& hitbox) override;
	virtual const bool IsRequired() const override;
private:
	std::shared_ptr<sf::Sprite> sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
	bool required;
};

#endif // HITBOX_COMPONENT_H