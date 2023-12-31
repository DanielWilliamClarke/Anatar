#ifndef INERT_HITBOX_COMPONENT_H
#define INERT_HITBOX_COMPONENT_H


#include <memory>

#include "i_hitbox_component.h"

class InertHitboxComponent : public IHitboxComponent
{
public:
	InertHitboxComponent() = default;
	~InertHitboxComponent() override = default;

	void Update(sf::Vector2f position) override {};
    void Draw(const std::shared_ptr<IRenderer>& renderer) override {};

	void Set(sf::Vector2f position, float offsetX, float offsetY, float width, float height) override {};
	virtual sf::FloatRect Get() const override { return {}; };
};

#endif // INERT_HITBOX_COMPONENT_H