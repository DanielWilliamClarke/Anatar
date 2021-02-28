#include "projectile.h"

#include "../util/i_glow_shader_renderer.h"
#include "../entity/entity.h"
#include "../components/hitbox/i_hitbox_component.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config)
	: Bullet(position, velocity, config),
	round(config.shapeBuilder())
{
	this->round->setFillColor(config.color);
	auto bounds = this->round->getLocalBounds();
	this->round->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Projectile::Update(float dt, float worldSpeed)
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

void Projectile::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->ExposeTarget().draw(*round);
	renderer->AddGlowAtPosition(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);
}

std::vector<EntityCollision> Projectile::DetectCollisions(std::vector<std::shared_ptr<Entity>> targets)
{
	std::vector<std::shared_ptr<Entity>> culledTargets;
	std::copy_if(targets.begin(), targets.end(), std::back_inserter(culledTargets),
		[this](std::shared_ptr<Entity> entity) -> bool {
			return entity->DetectCollisionWithRay(this->position, this->velocity)->intersects;
		});

	// sort elements closest to furthest
	std::sort(culledTargets.begin(), culledTargets.end(),
		[this](EntityCollision collisionA, EntityCollision collisionB) -> bool {
			auto distanceA = collisionA.target->DistanceTo(this->position);
			auto distanceB = collisionB.target->DistanceTo(this->position);
			return distanceA < distanceB;
		});

	std::vector<EntityCollision> collisions;
	for (auto& t : culledTargets)
	{
		if (t->DetectCollision(this->round->getGlobalBounds()))
		{
			collisions.push_back(EntityCollision(t, this->position));

			if (!config.penetrating) {
				this->spent = true;
				break;
			}
		}
	}

	return collisions;
}