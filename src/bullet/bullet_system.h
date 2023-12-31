#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H


#include <SFML/Graphics.hpp>
#include <memory>

#include "i_bullet_system.h"

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class IRenderer;

template<typename C, typename P>
class QuadTree;

class BulletSystem : public IBulletSystem
{
public:
	explicit BulletSystem(sf::FloatRect bounds);
    ~BulletSystem() override = default;

	std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) override;
	void Update(const CollisionQuadTree& quadTree, float dt, float worldSpeed) override;
	void Draw(const std::shared_ptr<IRenderer>& renderer, float interp) override;

private:

	void AddBullet(const std::shared_ptr<Bullet>& bullet);
	void EraseBullets();
	static void ResolveCollisions(const std::vector<std::shared_ptr<Collision>>& collisions) ;

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::FloatRect bounds;
};

#endif