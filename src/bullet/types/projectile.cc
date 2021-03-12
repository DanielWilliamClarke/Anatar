#include "projectile.h"

#include <array>

#include "util/math_utils.h"

#include "renderer/i_renderer.h"
#include "entity/entity.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"
#include "quad_tree/quad_tree.h"

Projectile::Projectile(BulletTrajectory& trajectory, BulletConfig& config)
	: Bullet(trajectory, config),
	round(config.shapeBuilder())
{
	this->round->setFillColor(config.color);
	auto bounds = this->round->getLocalBounds();
	this->round->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Projectile::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position += ((this->velocity * this->speed) + sf::Vector2f(worldSpeed, 0.0f)) * dt;
	this->round->setPosition(this->position);

	if (config.rotation)
	{
		this->round->rotate(config.rotation);
	}

	if (config.lifeTime > 0)
	{
		this->accumulator += dt;

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

void Projectile::Draw(std::shared_ptr<IRenderer> renderer, float interp)
{
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->GetTarget().draw(*round);
	renderer->AddGlow(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);

	auto line = std::array<sf::Vertex, 2>{
		sf::Vertex(this->position),
		sf::Vertex(this->position + (this->velocity * 15.0f))
	};
	renderer->GetDebugTarget().draw(line.data(), 2, sf::Lines);
}

std::vector<std::shared_ptr<EntityCollision>> Projectile::DetectCollisions(std::shared_ptr<CollisionQuadTree> quadTree)
{
	std::vector<std::shared_ptr<EntityCollision>> collisions;
	auto query = RectangleQuery(this->round->getGlobalBounds());
	quadTree->Query(&query, collisions,
		[this](std::shared_ptr<Entity> target) -> std::shared_ptr<EntityCollision> {
			if (target != this->GetOwner() &&
				target->GetTag() != this->GetOwner()->GetTag() &&
				target->DetectCollision(this->position))
			{
				return std::make_shared<EntityCollision>(target, this->position);
			}
			return nullptr;
		});

	if (collisions.size() && !config.penetrating)
	{
		this->spent = true;
	}

	return collisions;
}