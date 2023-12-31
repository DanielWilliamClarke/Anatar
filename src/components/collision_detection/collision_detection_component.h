#ifndef COLLISION_DETECTION_COMPONENT_H
#define COLLISION_DETECTION_COMPONENT_H


#include <SFML/Graphics.hpp>
#include <memory>

#include "i_collision_detection_component.h"

class IRayCaster;

class CollisionDetectionComponent : public ICollisionDetectionComponent
{
public:
	explicit CollisionDetectionComponent(std::shared_ptr<IRayCaster> rayCaster);
	~CollisionDetectionComponent() override = default;

    std::shared_ptr<sf::Vector2f> DetectCollision(const sf::FloatRect& box, const sf::Vector2f& position, bool ray = false, const sf::Vector2f& dir = sf::Vector2f()) const override;
    bool DetectIntersection(const sf::FloatRect& boxA, const sf::FloatRect& boxB) const override;
private:
	std::shared_ptr<IRayCaster> rayCaster;
};

#endif //COLLISION_DETECTION_COMPONENT_H