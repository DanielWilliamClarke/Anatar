#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H


#include <memory>

#include "i_hitbox_component.h"

class IRenderer;

class HitboxComponent : public IHitboxComponent
{
public:
	HitboxComponent(sf::Color colour);
	virtual ~HitboxComponent() = default;

	virtual void Update(sf::Vector2f position) override;
	virtual void Draw(std::shared_ptr<IRenderer> renderer) override;

	virtual void Set(sf::Vector2f position, float offsetX, float offsetY, float width, float height) override;
	virtual sf::FloatRect Get() const;
private:
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
};

#endif // HITBOX_COMPONENT_H