#include <SFML/Graphics.hpp>
#include "hitbox_component.h"

HitboxComponent::HitboxComponent(sf::Color outline)
	: offsetX(0), offsetY(0)
{
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(outline);
}

void HitboxComponent::SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height) {
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->sprite = sprite;

	const auto position = this->sprite->getPosition();
	this->hitbox.setPosition(position.x + offsetX, position.y + offsetY);
	this->hitbox.setSize(sf::Vector2f(width, height));
}

void HitboxComponent::Update()
{
	const auto position = this->sprite->getPosition();
	this->hitbox.setPosition(position.x + this->offsetX, position.y + this->offsetY);
}

void HitboxComponent::Draw(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}

bool HitboxComponent::Intersects(const sf::FloatRect& hitbox)
{
	return this->hitbox.getGlobalBounds().intersects(hitbox);
}