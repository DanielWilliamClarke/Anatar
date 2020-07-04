#include "bullet.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config)
	: position(position), lastPosition(position), velocity(velocity), round(config.shapeBuilder()), config(config), spent(false)
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
}

void Bullet::Draw(sf::RenderTarget& target, sf::Sprite& glowSprite, sf::Shader& shader, float interp)
{
	auto color = this->round->getFillColor();
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));

	target.draw(*round);

	shader.setUniform("frag_LightOrigin", this->round->getPosition());
	shader.setUniform("frag_LightColor", sf::Vector3f(color.r, color.g, color.b));
	shader.setUniform("frag_LightAttenuation", 200.0f);

	sf::RenderStates states;
	states.shader = &shader;
	states.blendMode = sf::BlendAdd;

	target.draw(glowSprite, states);
}

void Bullet::CollisionDetected()
{
	spent = true;
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