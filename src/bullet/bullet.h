#ifndef BULLET_H
#define BULLET_H
#pragma once

#include <SFML/Graphics.hpp>

struct BulletConfig
{
	std::shared_ptr<sf::Shape> shape;
	sf::Color color;
	float rotation;

	float speed;
	bool penetrating;
	float damage;

	BulletConfig(std::shared_ptr<sf::Shape> shape, sf::Color color, float rotation, float speed, bool penetrating, float damage)
		: shape(shape), color(color), speed(speed), rotation(rotation), penetrating(penetrating), damage(damage)
	{}
};

class Bullet
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config);
	virtual ~Bullet() = default;

	void Update(float dt, float worldSpeed);
	void Draw(sf::RenderTarget& target, float interp);

	void CollisionDetected();
	bool isSpent() const;

	std::shared_ptr<sf::Shape> GetRound() const;
	BulletConfig GetConfig() const;

private:
	std::shared_ptr<sf::Shape> round; // Holds the bullet shape / position etc
	sf::Vector2f position;
	sf::Vector2f lastPosition;
	sf::Vector2f velocity;
	bool spent; // used in hit detection

	BulletConfig config;
};

#endif // BULLET_H
