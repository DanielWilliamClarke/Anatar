#include "beam.h"

#include "util/math_helpers.h"

#include "entity/entity.h"
#include "util/i_glow_shader_renderer.h"
#include "util/i_ray_caster.h"

Beam::Beam(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config, std::shared_ptr<IRayCaster> rayCaster, sf::FloatRect bounds, float damageRate)
	: Bullet(position, velocity, config),
	rayCaster(rayCaster),
	round(std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 5.0f))),
	collisionPosition(std::shared_ptr<sf::Vector2f>(nullptr)),
	bounds(bounds),
	damageRateAccumulator(0.0f),
	damageRate(damageRate),
	damageCache(config.damage)
{
	this->round->setFillColor(config.color);
	auto roundBounds = this->round->getLocalBounds();
	this->round->setOrigin(0, roundBounds.height / 2.0f);
	this->round->setRotation(AngleConversion::ToDegrees(atan2(this->velocity.y, this->velocity.x)));
}

void Beam::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position = this->config.owner->GetPosition();
	this->round->setPosition(this->position);

	auto beamEnd = collisionPosition ?
		*collisionPosition :
		this->rayCaster->RayBoxIntersects(this->position, this->velocity, bounds)->point;

	this->round->setSize(
		sf::Vector2f(
			Dimensions::DistanceBetween(this->config.owner->GetPosition(), beamEnd),
			this->round->getSize().y));

	config.damage = 0;
	this->damageRateAccumulator += this->damageClock.restart().asSeconds();
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

	if (collisionPosition) {
		renderer->AddGlowAtPosition(*collisionPosition, this->round->getFillColor(), config.glowAttenuation);
	}
}

std::vector<EntityCollision> Beam::DetectCollisions(std::vector<std::shared_ptr<Entity>> targets)
{
	// Clear collision point before detection
	collisionPosition = nullptr;

	std::vector<EntityCollision> collisions;
	for (auto& t : targets)
	{
		auto c = t->DetectCollisionWithRay(this->position, this->velocity);
		if (c->intersects) {
			collisions.push_back(EntityCollision(t, c->point));
		}
	}

	std::sort(collisions.begin(), collisions.end(),
		[this](EntityCollision collisionA, EntityCollision collisionB) -> bool {
			auto distanceA = Dimensions::ManhattanDistance(collisionA.target->GetPosition(), this->position);
			auto distanceB = Dimensions::ManhattanDistance(collisionB.target->GetPosition(), this->position);
			return distanceA < distanceB;
		});

	// Set collision point to hit the first entity if the beam cant penetrate
	if (!config.penetrating && collisions.size())
	{
		collisionPosition = std::make_shared<sf::Vector2f>(collisions.front().point);
	}

	return collisions;
}

void Beam::Reignite()
{
	this->accumulator = 0;
}

