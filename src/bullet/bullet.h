#ifndef BULLET_H
#define BULLET_H
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <list>

#include "quad_tree/quad_tree.h"

class IGlowShaderRenderer;
class Entity;

enum class AFFINITY :int { LEFT = -1, RIGHT = 1 };

struct BulletConfig
{
	std::function<std::shared_ptr<sf::Shape>(void)> shapeBuilder;
	std::shared_ptr<Entity> owner;

	sf::Color color;
	float glowAttenuation;

	float rotation;
	float speed;
	AFFINITY affinity;

	bool penetrating;
	float damage;
	float lifeTime;

	BulletConfig(
		std::shared_ptr<Entity> owner,
		std::function<std::shared_ptr<sf::Shape>(void)> shapeBuilder,
		sf::Color color, 
		float glowAttenuation,
		float rotation, 
		float speed, 
		AFFINITY affinity,
		bool penetrating, 
		float damage, 
		float lifeTime = 0.0f)
		: owner(owner), 
		shapeBuilder(shapeBuilder),
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

struct EntityCollision {
	std::shared_ptr<Entity> target;
	sf::Vector2f point;

	EntityCollision(std::shared_ptr<Entity> target, sf::Vector2f point = sf::Vector2f())
		: target(target), point(point)
	{}
};

class Bullet
{
public:
	Bullet(BulletTrajectory& trajectory, BulletConfig& config);
	virtual ~Bullet() = default;

	virtual void Update(float dt, float worldSpeed) = 0;
	virtual void Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp) = 0;
	virtual std::vector<EntityCollision> DetectCollisions(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree) = 0;

	bool isSpent() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetVelocity() const;
	float GetDamage() const;
	std::shared_ptr<Entity> GetOwner() const;

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
