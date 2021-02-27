#include "beam.h"

#include "../entity/entity.h"
#include "../util/i_glow_shader_renderer.h"

Beam::Beam(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config, sf::FloatRect bounds, float damageRate)
	: Bullet(position, velocity, config),
	round(std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 3.0f))),
	collisionPosition(&sf::Vector2f(bounds.width, position.y)),
	bounds(bounds),
	damageRateAccumulator(0.0f),
	damageRate(damageRate),
	damageCache(config.damage)
{
	this->round->setFillColor(config.color);
}

void Beam::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position = this->config.owner->GetPosition();
	this->round->setPosition(this->position);

	auto beamEnd = sf::Vector2f(collisionPosition ? collisionPosition->x : this->bounds.width, this->position.y);
	this->round->setSize(
		sf::Vector2f(
			this->config.owner->DistanceTo(beamEnd),
			this->round->getSize().y));

	config.damage = 0;
	this->damageRateAccumulator += this->damageClock .restart().asSeconds();
	if (this->damageRateAccumulator >= this->damageRate)
	{   
		config.damage = damageCache;             
		this->damageRateAccumulator = 0;
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

void Beam::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->ExposeTarget().draw(*round);
	renderer->AddGlowAtPosition(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);
}


void Beam::CollisionDetected(sf::Vector2f* point)
{
	collisionPosition = point;
}

std::shared_ptr<sf::Shape> Beam::GetRound() const
{
	return round;
}

void Beam::Reignite()
{
	this->accumulator = 0;
}

