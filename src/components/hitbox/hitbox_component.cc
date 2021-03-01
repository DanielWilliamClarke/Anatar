#include "hitbox_component.h"

#include "util/i_ray_caster.h"

HitboxComponent::HitboxComponent(std::shared_ptr<IRayCaster> rayCaster, sf::Color colour)
	: rayCaster(rayCaster), offsetX(0), offsetY(0), required(false)
{
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(colour);
}

void HitboxComponent::SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height) {
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->sprite = sprite;

	const auto position = this->sprite->getPosition();
	this->hitbox.setPosition(position.x + offsetX, position.y + offsetY);
	this->hitbox.setSize(sf::Vector2f(width, height));
	required = true;
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

bool HitboxComponent::Contains(const sf::Vector2f& position)
{
	return this->hitbox.getGlobalBounds().contains(position);
}

std::shared_ptr<RayIntersection> HitboxComponent::IntersectsWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const
{
	return this->rayCaster->RayBoxIntersects(origin, direction, this->hitbox.getGlobalBounds());
}

const bool HitboxComponent::IsRequired() const
{
	return required;
}

