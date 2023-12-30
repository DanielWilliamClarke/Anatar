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

	virtual std::shared_ptr<sf::Vector2f> DetectCollision(const sf::FloatRect& box, const sf::Vector2f& position, bool ray = false, const sf::Vector2f& dir = sf::Vector2f()) const = 0;
	virtual bool DetechIntersection(const sf::FloatRect& boxA, const sf::FloatRect& boxB) const = 0;
};

#endif //I_COLLISION_DETECTION_COMPONENT_H