#pragma once
#include <memory>

#include "i_hitbox_component.h"

class HitboxComponent: public IHitboxComponent
{
public: 
	HitboxComponent();
	virtual ~HitboxComponent() = default;

	virtual void SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height);
	virtual void Update();
	virtual void Draw(sf::RenderTarget& target);
	virtual bool Intersects(const sf::FloatRect& hitbox);

private:
	std::shared_ptr<sf::Sprite> sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
};