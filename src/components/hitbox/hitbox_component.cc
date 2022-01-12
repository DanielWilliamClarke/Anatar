#include "hitbox_component.h"

#include "renderer/i_renderer.h"

HitboxComponent::HitboxComponent(sf::Color colour)
	: offsetX(0), offsetY(0)
{
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(colour);
}

void HitboxComponent::SetSprite(sf::Vector2f position, float offsetX, float offsetY, float width, float height) {
	this->offsetX = offsetX;
	this->offsetY = offsetY;

	this->hitbox.setPosition(position.x + offsetX, position.y + offsetY);
	this->hitbox.setSize(sf::Vector2f(width, height));
}

void HitboxComponent::Update(sf::Vector2f position)
{
	this->hitbox.setPosition(position.x + this->offsetX, position.y + this->offsetY);
}

void HitboxComponent::Draw(std::shared_ptr<IRenderer> renderer)
{
	renderer->GetDebugTarget().draw(this->hitbox);
}

sf::FloatRect HitboxComponent::GetHitbox() const {
	return this->hitbox.getGlobalBounds();
}