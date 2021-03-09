#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#pragma once
#include <memory>

#include "i_hitbox_component.h"

struct RayIntersection;
class IRayCaster;
class IRenderer;

class HitboxComponent : public IHitboxComponent
{
public:
	HitboxComponent(std::shared_ptr<IRayCaster> rayCaster, sf::Color colour);
	virtual ~HitboxComponent() = default;

	virtual void SetSprite(std::shared_ptr<sf::Sprite> sprite, float offsetX, float offsetY, float width, float height) override;
	virtual void Update() override;
	virtual void Draw(std::shared_ptr<IRenderer> renderer) override;
	virtual bool Intersects(const sf::FloatRect& hitbox) override;
	virtual bool Contains(const sf::Vector2f& position) override;
	virtual std::shared_ptr<RayIntersection> IntersectsWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const override;
	virtual const bool IsRequired() const override;
private:
	std::shared_ptr<IRayCaster> rayCaster;
	std::shared_ptr<sf::Sprite> sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
	bool required;
};

#endif // HITBOX_COMPONENT_H