#include "bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig& config)
	: position(position), lastPosition(position), velocity(velocity), round(sf::CircleShape(config.radius)), config(config), spent(false)
{
	this->round.setFillColor(config.color);
}

void Bullet::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position += (this->velocity + sf::Vector2f(worldSpeed, 0.0f)) * dt;
	this->round.setPosition(this->position);
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

BulletConfig Bullet::GetConfig() const
{
	return config;
}