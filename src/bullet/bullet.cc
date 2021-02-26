#include "bullet.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config)
	: position(position),
	lastPosition(position),
	velocity(velocity),
	config(config),
	spent(false),
	accumulator(0.0f),
	minFadeout(0.8f),
	maxFadeout(1.0f)
{
}

bool Bullet::isSpent() const
{
	return spent;
}

BulletConfig Bullet::GetConfig() const
{
	return config;
}

sf::Vector2f Bullet::GetPosition() const
{
	return position;
}

sf::Vector2f Bullet::GetVelocity() const
{
	return velocity;
}

std::pair<float, bool> Bullet::GetDamage() const
{
	return std::make_pair(config.damage, config.penetrating);
}

std::shared_ptr<Entity> Bullet::GetOwner() const
{
	return config.owner;
}