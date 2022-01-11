#ifndef BULLET_H
#define BULLET_H
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <list>

struct Collision;
class IRenderer;

template<typename C>
class QuadTree;

enum class AFFINITY :int { LEFT = -1, RIGHT = 1 };

struct BulletCallbacks {

	std::function<void(bool, float)> collisionResolver;
	std::function<sf::Vector2f(void)> ownerPositionSampler;
	std::function<std::shared_ptr<sf::Shape>(void)> shapeBuilder;

	BulletCallbacks(
		std::function<void(bool, float)> collisionResolver,
		std::function<sf::Vector2f(void)> ownerPositionSampler,
		std::function<std::shared_ptr<sf::Shape>(void)> shapeBuilder)
		: collisionResolver(collisionResolver),
		ownerPositionSampler(ownerPositionSampler),
		shapeBuilder(shapeBuilder)
	{}
};

struct BulletConfig
{
	BulletCallbacks callbacks;
	std::string tag;

	sf::Color color;
	float glowAttenuation;

	float rotation;
	float speed;
	AFFINITY affinity;

	bool penetrating;
	float damage;
	float lifeTime;

	BulletConfig(
		BulletCallbacks callbacks,
		std::string tag,
		sf::Color color, 
		float glowAttenuation,
		float rotation, 
		float speed, 
		AFFINITY affinity,
		bool penetrating, 
		float damage, 
		float lifeTime = 20.0f)
		: callbacks(callbacks),
		tag(tag),
		color(color),
		glowAttenuation(glowAttenuation),
		speed(speed),
		affinity(affinity), 
		rotation(rotation),
		penetrating(penetrating),
		damage(damage), 
		lifeTime(lifeTime)
	{}
};

struct BulletTrajectory
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;

	BulletTrajectory(sf::Vector2f position, sf::Vector2f velocity, float speed)
		: position(position), velocity(velocity), speed(speed)
	{}
};

class Bullet : public std::enable_shared_from_this<Bullet>
{
public:
	Bullet(BulletTrajectory& trajectory, BulletConfig& config);
	virtual ~Bullet() = default;

	virtual void Update(float dt, float worldSpeed) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) = 0;
	virtual std::vector<std::shared_ptr<Collision>> DetectCollisions(std::shared_ptr<QuadTree<Collision>> quadTree) = 0;

	bool isSpent() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetVelocity() const;
	float GetDamage() const;
	std::string GetTag() const;
	std::function<void(bool, float)> GetCollisionResolver() const;


protected:
	BulletConfig config;
	sf::Vector2f position;
	sf::Vector2f lastPosition;
	sf::Vector2f velocity;
	float speed;
	bool spent; // used in hit detection

	float accumulator;
	float minFadeout;
	float maxFadeout;
};

#endif // BULLET_H
