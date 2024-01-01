#ifndef PROJECTILE_H
#define PROJECTILE_H


#include <SFML/Graphics.hpp>

#include "bullet/bullet.h"
#include "quad_tree/quad_tree.h"

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;

class Projectile : public Bullet
{
public:
	Projectile(BulletTrajectory& trajectory, BulletConfig& config);
	~Projectile() override = default;

	void Update(float dt, float worldSpeed) override;
	void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) override;
	std::vector<std::shared_ptr<Collision>> DetectCollisions(const CollisionQuadTree& quadTree) override;

protected:
	std::shared_ptr<sf::Shape> round; // Holds the bullet shape / position etc
};

#endif
