#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H


#include <memory>

#include "i_hitbox_component.h"

class IRenderer;

class HitboxComponent : public IHitboxComponent
{
public:
	explicit HitboxComponent(sf::Color colour);
	~HitboxComponent() override = default;

	void Update(sf::Vector2f position) override;
    void Draw(const std::shared_ptr<IRenderer>& renderer) override;

	void Set(sf::Vector2f position, float offsetX, float offsetY, float width, float height) override;
	sf::FloatRect Get() const override;
private:
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
};

#endif // HITBOX_COMPONENT_H