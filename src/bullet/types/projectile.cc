#include "projectile.h"

#include <array>

#include "util/math_utils.h"

#include "renderer/i_renderer.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"
#include "quad_tree/quad_tree.h"
#include "bullet/collision.h"

Projectile::Projectile(BulletTrajectory& trajectory, BulletConfig& config)
	: Bullet(trajectory, config),
	round(config.callbacks.shapeBuilder())
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

std::vector<std::shared_ptr<Collision>> Projectile::DetectCollisions(std::shared_ptr<QuadTree<Collision>> quadTree)
{
	std::vector<std::shared_ptr<Collision>> collisions;
	auto query = RectangleQuery(this->round->getGlobalBounds());

	quadTree->Query(&query, collisions,
		[this](std::shared_ptr<Point> point) -> std::shared_ptr<Collision> {
			if (point->tag != this->GetTag() && point->collisionTest(this->position, this->velocity, false))
			{
				return std::make_shared<Collision>(this->shared_from_this(), point);
			}
			return nullptr;
		});

	if (collisions.size() && !config.penetrating)
	{
		this->spent = true;
	}

	return collisions;
}