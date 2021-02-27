#include "hitbox_component.h"

HitboxComponent::HitboxComponent(sf::Color colour)
	: offsetX(0), offsetY(0), required(false)
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

// See https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection for details
std::shared_ptr<RayIntersection> HitboxComponent::IntersectsWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const
{
	auto bounds = this->hitbox.getGlobalBounds();

	auto top = bounds.top;
	auto bottom = bounds.top + bounds.height;
	auto left = bounds.left;
	auto right = bounds.left + bounds.width;

	// Here I define each line of the hitbox
	auto lines = std::vector< std::pair<sf::Vector2f, sf::Vector2f>>({
		std::pair<sf::Vector2f, sf::Vector2f>( // left
			sf::Vector2f(left, top),
			sf::Vector2f(left, bottom)),
		std::pair<sf::Vector2f, sf::Vector2f>( // bottom
			sf::Vector2f(left, bottom),
			sf::Vector2f(right, bottom)),
		 std::pair<sf::Vector2f, sf::Vector2f>( // right
			sf::Vector2f(right, bottom),
			sf::Vector2f(right, top)),
		std::pair<sf::Vector2f, sf::Vector2f>( // top
			sf::Vector2f(right, top),
			sf::Vector2f(left, top))
		});

	// Define ray
	auto x3 = origin.x;
	auto y3 = origin.y;
	auto x4 = origin.x + direction.x;
	auto y4 = origin.y + direction.y;

	for (auto& line : lines) {

		auto x1 = line.first.x;
		auto y1 = line.first.y;
		auto x2 = line.second.x;
		auto y2 = line.second.y;


		auto den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0) {
			continue;
		}

		auto t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		auto u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0 && t < 1 && u > 0) {
			return std::make_shared<RayIntersection>(
				true,
				sf::Vector2f(
					x1 + t * (x2 - x1),
					y1 + t * (y2 - y1)));
		}
	}

	return std::make_shared<RayIntersection>(false);
}

const bool HitboxComponent::IsRequired() const
{
	return required;
}

