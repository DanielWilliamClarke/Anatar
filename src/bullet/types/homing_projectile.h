#ifndef HOMING_PROJECTILE_H
#define HOMING_PROJECTILE_H


#include <SFML/Graphics.hpp>
#include <array>

#include "projectile.h"

class HomingProjectile : public Projectile
{
public:
	HomingProjectile(BulletTrajectory& trajectory, BulletConfig& config);
	virtual ~HomingProjectile() = default;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) override;
	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(const std::shared_ptr<QuadTree<Collision, CollisionMediators>>& quadTree) override;

private:
	std::array<sf::Vertex, 2> line;
	sf::FloatRect zone;
};

#endif // HOMING_PROJECTILE_H