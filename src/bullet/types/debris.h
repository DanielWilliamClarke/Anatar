#ifndef DEBRIS_H
#define DEBRIS_H


#include <SFML/Graphics.hpp>

#include "projectile.h"

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;

class Debris : public Projectile
{
public:
	Debris(BulletTrajectory& trajectory, BulletConfig& config) 
		: Projectile(trajectory, config)
	{}

	virtual ~Debris() = default;

	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(const std::shared_ptr<QuadTree<Collision, CollisionMediators>>& quadTree) override { return {}; }
};

#endif // DEBRIS_H