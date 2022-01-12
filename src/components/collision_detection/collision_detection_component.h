#ifndef COLLISION_DETECTION_COMPONENT_H
#define COLLISION_DETECTION_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "i_collision_detection_component.h"

class IRayCaster;

class CollisionDetectionComponent : public ICollisionDetectionComponent
{
public:
	CollisionDetectionComponent(std::shared_ptr<IRayCaster> rayCaster);
	virtual ~CollisionDetectionComponent() = default;
	virtual std::shared_ptr<sf::Vector2f> DetectCollision(const sf::FloatRect& box, const sf::Vector2f& position, bool ray = false, const sf::Vector2f& dir = sf::Vector2f()) const override;
	virtual bool DetechIntersection(const sf::FloatRect& boxA, const sf::FloatRect& boxB) const override;
private:
	std::shared_ptr<IRayCaster> rayCaster;
};

#endif //COLLISION_DETECTION_COMPONENT_H