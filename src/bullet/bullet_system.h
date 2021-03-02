#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <mutex>

#include "i_bullet_system.h"

class Bullet;
struct BulletConfig;
struct BulletTrajectory;
class Entity;
class IGlowShaderRenderer;
class IThreadedWorkload;

class BulletSystem : public IBulletSystem
{
public:
	enum affinities { LEFT = -1, RIGHT = 1 };

	BulletSystem(std::shared_ptr<IThreadedWorkload> threadableWorkload, sf::FloatRect bounds, int affinity);
	virtual ~BulletSystem() = default;

	virtual std::shared_ptr<Bullet> FireBullet(std::shared_ptr<IBulletFactory> bulletFactory, BulletTrajectory& trajectory, BulletConfig& config) override;
	void Update(float dt, float worldSpeed, std::vector<std::shared_ptr<Entity>>& targets);
	void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp);

private:

	void AddBullet(std::shared_ptr<Bullet> bullet);
	void MultiThreadedUpdate(float dt, float worldSpeed, std::vector<std::shared_ptr<Entity>>& targets);
	void UpdateBullets(std::vector<std::shared_ptr<Bullet>>& bullets, std::vector<std::shared_ptr<Entity>>& collisionTargets, float& dt, float& worldSpeed) const;
	void EraseBullets();

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::FloatRect bounds;
	int affinity;

	std::shared_ptr<IThreadedWorkload> threadableWorkload;
	std::mutex mutex;
};

#endif // BULLET_SYSTEM_H