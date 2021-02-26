#include "bullet.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>

#include "../util/i_glow_shader_renderer.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config)
	: position(position),
	lastPosition(position),
	collisionPosition(sf::Vector2f()),
	velocity(velocity), 
	round(config.shapeBuilder()), 
	config(config),
	spent(false),
	accumulator(0.0f),
	minFadeout(0.8f),
	maxFadeout(1.0f)
{
	this->round->setFillColor(config.color);
	auto bounds = this->round->getLocalBounds();
	this->round->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Bullet::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position += (this->velocity + sf::Vector2f(worldSpeed, 0.0f)) * dt;
	this->round->setPosition(this->position);

	if (config.rotation)
	{
		this->round->rotate(config.rotation);
	}

	if (config.lifeTime > 0)
	{
		this->accumulator += this->clock.restart().asSeconds();

		auto percentage = 1 - ((config.lifeTime - this->accumulator) / config.lifeTime);
		if (percentage > minFadeout && percentage <= maxFadeout)
		{
			auto localPercentage = (percentage - minFadeout) / (maxFadeout - minFadeout);
			this->round->setFillColor(sf::Color(
				(sf::Uint8)((sf::Color::Transparent.r - config.color.r) * localPercentage + config.color.r),
				(sf::Uint8)((sf::Color::Transparent.g - config.color.g) * localPercentage + config.color.g),
				(sf::Uint8)((sf::Color::Transparent.b - config.color.b) * localPercentage + config.color.b)));
		}

		if (this->accumulator >= config.lifeTime)
		{
			spent = true;
		}
	}
}

void Bullet::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->ExposeTarget().draw(*round);
	renderer->AddGlowAtPosition(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);
}

void Bullet::CollisionDetected(sf::Vector2f point)
{
	spent = config.penetrating ? false : true;
	collisionPosition = point;
}

bool Bullet::isSpent() const
{
	return spent;
}

std::shared_ptr<sf::Shape> Bullet::GetRound() const
{
	return round;
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