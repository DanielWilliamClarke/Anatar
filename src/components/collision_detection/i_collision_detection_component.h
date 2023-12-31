#ifndef I_COLLISION_DETECTION_COMPONENT_H
#define I_COLLISION_DETECTION_COMPONENT_H


#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class ICollisionDetectionComponent
{
public:
	ICollisionDetectionComponent() = default;
	virtual ~ICollisionDetectionComponent() = default;

    [[nodiscard]] virtual std::shared_ptr<sf::Vector2f> DetectCollision(const sf::FloatRect& box, const sf::Vector2f& position, bool ray = false, const sf::Vector2f& dir = sf::Vector2f()) const = 0;
	[[nodiscard]] virtual bool DetectIntersection(const sf::FloatRect& boxA, const sf::FloatRect& boxB) const = 0;
};

#endif