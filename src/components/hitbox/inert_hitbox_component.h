#ifndef INERT_HITBOX_COMPONENT_H
#define INERT_HITBOX_COMPONENT_H


#include <memory>

#include "i_hitbox_component.h"

class InertHitboxComponent : public IHitboxComponent
{
public:
	InertHitboxComponent() = default;
	virtual ~InertHitboxComponent() = default;

	virtual void Update(sf::Vector2f position) override {};
	virtual void Draw(std::shared_ptr<IRenderer> renderer) override {};

	virtual void Set(sf::Vector2f position, float offsetX, float offsetY, float width, float height) override {};
	virtual sf::FloatRect Get() const { return sf::FloatRect(); };
};

#endif // INERT_HITBOX_COMPONENT_H