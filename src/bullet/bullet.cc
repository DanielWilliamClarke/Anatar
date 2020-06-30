#include "bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity, sf::Color colour, float radius)
	: position(position), lastPosition(position), velocity(position), round(sf::CircleShape(radius)), spent(false)
{
	this->round.setFillColor(colour);
}

void Bullet::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position += (this->velocity + sf::Vector2f(0.0f, worldSpeed)) * dt;
}

void Bullet::Draw(sf::RenderTarget& target, float interp) 
{
	this->round.setPosition(position * interp + lastPosition * (1.0f - interp));
	target.draw(round);
}

void Bullet::CollisionDetected()
{
	spent = true;
}

bool Bullet::isSpent() const
{
	return spent;
}

sf::CircleShape Bullet::GetRound() const
{
	return round;
}