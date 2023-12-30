#ifndef PROJECTILE_H
#define PROJECTILE_H


#include <SFML/Graphics.hpp>

#include "bullet/bullet.h"

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;

class Projectile : public Bullet
{
public:
	Projectile(BulletTrajectory& trajectory, BulletConfig& config);
	virtual ~Projectile() = default;

	virtual void Update(float dt, float worldSpeed) override;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) override;
	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(const std::shared_ptr<QuadTree<Collision, CollisionMediators>>& quadTree) override;

protected:

	std::shared_ptr<sf::Shape> round; // Holds the bullet shape / position etc
};

#endif // PROJECTILE_H
