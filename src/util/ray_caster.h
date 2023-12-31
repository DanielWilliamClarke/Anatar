#ifndef RAY_CASTER_H
#define RAY_CASTER_H


#include "i_ray_caster.h"

class RayCaster : public IRayCaster
{
public:
	RayCaster() = default;
	~RayCaster() override = default;

	[[nodiscard]] std::shared_ptr<RayIntersection> RayBoxIntersects(
        const sf::Vector2f& origin,
        const sf::Vector2f& direction,
        sf::FloatRect box
    ) const override;
};

#endif