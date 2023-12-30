#ifndef I_LOCAL_MOVEMENT_COMPONENT_H
#define I_LOCAL_MOVEMENT_COMPONENT_H


#include <SFML/Graphics.hpp>

class ILocalMovementComponent
{
public:
	ILocalMovementComponent() = default;
	virtual ~ILocalMovementComponent() = default;

	virtual sf::Vector2f Integrate(sf::Vector2f origin, const float& dt) = 0;
	virtual sf::Vector2f Interpolate(sf::Vector2f interpPosition) const = 0;
};

#endif //I_LOCAL_MOVEMENT_COMPONENT_H