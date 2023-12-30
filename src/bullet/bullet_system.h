#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H


#include <SFML/Graphics.hpp>
#include <memory>

#include "i_bullet_system.h"

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class IRenderer;

struct Collision;
struct CollisionMediators;

template<typename C, typename P>
class QuadTree;

class BulletSystem : public IBulletSystem
{
public:
	BulletSystem(sf::FloatRect bounds);
	virtual ~BulletSystem() = default;

	std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) override;
	void Update(const std::shared_ptr<QuadTree<Collision, CollisionMediators>>& quadTree, float dt, float worldSpeed);
	void Draw(const std::shared_ptr<IRenderer>& renderer, float interp);

private:

	void AddBullet(const std::shared_ptr<Bullet>& bullet);
	void EraseBullets();
	static void ResolveCollisions(const std::vector<std::shared_ptr<Collision>>& collisions) ;

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::FloatRect bounds;
};

#endif // BULLET_SYSTEM_H