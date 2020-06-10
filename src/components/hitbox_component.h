#pragma once

namespace sf {
	class Sprite;
	class RectangleShape;
	class Color;
	class RenderTarget;
}

class HitboxComponent
{
public: 
	HitboxComponent(sf::Color outline);
	virtual ~HitboxComponent() = default;

	void SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height);
	void Update();
	void Draw(sf::RenderTarget& target);
	bool Intersects(const sf::FloatRect& hitbox);

private:
	std::shared_ptr<sf::Sprite> sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
};