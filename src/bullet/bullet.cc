#include "bullet.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>

Bullet::Bullet(BulletTrajectory& trajectory, BulletConfig& config)
	: position(trajectory.position),
	lastPosition(trajectory.position),
	velocity(trajectory.velocity),
	speed(trajectory.speed),
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

sf::Vector2f Bullet::GetPosition() const
{
	return position;
}

sf::Vector2f Bullet::GetVelocity() const
{
	return velocity;
}

float Bullet::GetDamage() const
{
	return config.damage;
}

std::string Bullet::GetTag() const
{
	return config.tag;
}

std::function<void(bool, float)> Bullet::GetCollisionResolver() const {
	return config.callbacks.collisionResolver;
}