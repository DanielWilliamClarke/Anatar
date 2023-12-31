#ifndef I_HITBOX_COMPONENT_H
#define I_HITBOX_COMPONENT_H


#include <SFML/Graphics.hpp>
#include <memory>

class IRenderer;

class IHitboxComponent
{
public:
	IHitboxComponent() = default;
	virtual ~IHitboxComponent() = default;

	virtual void Update(sf::Vector2f position) = 0;
	virtual void Draw(const std::shared_ptr<IRenderer>& renderer) = 0;

	virtual void Set(sf::Vector2f position, float offsetX, float offsetY, float width, float height) = 0;
	[[nodiscard]] virtual sf::FloatRect Get() const = 0;
};

#endif //I_HITBOX_COMPONENT_H