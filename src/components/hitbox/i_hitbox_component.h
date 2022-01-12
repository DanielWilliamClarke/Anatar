#ifndef I_HITBOX_COMPONENT_H
#define I_HITBOX_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

struct RayIntersection;
class IRenderer;

class IHitboxComponent
{
public:
	IHitboxComponent() = default;
	virtual ~IHitboxComponent() = default;

	virtual void SetSprite(sf::Vector2f position, float offsetX, float offsetY, float width, float height) = 0;
	virtual void Update(sf::Vector2f position) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer) = 0;
	virtual sf::FloatRect GetHitbox() const = 0;
};

#endif //I_HITBOX_COMPONENT_H