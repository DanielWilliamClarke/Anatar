#include "projectile.h"

#include "util/math_utils.h"

#include "util/i_glow_shader_renderer.h"
#include "entity/entity.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"

Projectile::Projectile(BulletTrajectory& trajectory, BulletConfig config)
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

void Projectile::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->ExposeTarget().draw(*round);
	renderer->AddGlowAtPosition(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);
}

std::vector<EntityCollision> Projectile::DetectCollisions(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree)
{
	std::vector<Point<std::shared_ptr<Entity>>> targets;
	auto query = RectangleQuery(this->round->getGlobalBounds());
	quadTree->Query(&query, targets, [&](std::shared_ptr<Entity> target) -> bool {
		return target->DetectCollision(this->position);
	});

	std::vector<EntityCollision> collisions;
	if (targets.size())
	{
		collisions.push_back(EntityCollision(targets.front().data, this->position));
		if (!config.penetrating) {
			this->spent = true;
		}
	}

	return collisions;
}

std::shared_ptr<Entity> Projectile::FindClosest(std::vector<std::shared_ptr<Entity>> targets) const
{
	if (targets.size() == 1)
	{
		return targets.front();
	}

	std::shared_ptr<Entity> closest = nullptr;
	float minDistance = std::numeric_limits<float>::infinity();
	for (auto& t : targets)
	{
		auto distance = Dimensions::ManhattanDistance(this->position, t->GetPosition());
		if (distance < minDistance) {
			minDistance = distance;
			closest = t;
		}
	}
	return closest;
}