#ifndef BULLET_H
#define BULLET_H
#pragma once

#include <SFML/Graphics.hpp>

struct BulletConfig
{
	sf::Color color;
	float radius;

	bool penetrating;
	float damage;

	BulletConfig(sf::Color color, float radius, bool penetrating, float damage) 
		: color(color), radius(radius), penetrating(penetrating), damage(damage)
	{}
};

class Bullet
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config);
	virtual ~Bullet() = default;

	void Update(float dt, float worldSpeed);
	void Draw(sf::RenderTarget& target, float interp);

	void CollisionDetected();
	bool isSpent() const;

	sf::CircleShape GetRound() const;
	BulletConfig GetConfig() const;

private:
	sf::CircleShape round; // Holds the bullet shape / position etc
	sf::Vector2f position;
	sf::Vector2f lastPosition;
	sf::Vector2f velocity;
	bool spent; // used in hit detection

	BulletConfig& config;
};

#endif // BULLET_H
