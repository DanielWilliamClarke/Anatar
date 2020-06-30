#ifndef BULLET_H
#define BULLET_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f velocity, sf::Color colour, float radius);
	virtual ~Bullet() = default;

	void Update(float dt, float worldSpeed);
	void Draw(sf::RenderTarget& target, float interp);

	void CollisionDetected();
	bool isSpent() const;

	sf::CircleShape GetRound() const;

private:
	sf::CircleShape round; // Holds the bullet shape / position etc
	sf::Vector2f position;
	sf::Vector2f lastPosition;
	sf::Vector2f velocity;
	bool spent; // used in hit detection
};

#endif // BULLET_H
