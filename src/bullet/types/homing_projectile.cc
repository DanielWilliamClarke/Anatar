#include "homing_projectile.h"

#include "util/math_utils.h"

#include "util/i_glow_shader_renderer.h"
#include "entity/entity.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"

HomingProjectile::HomingProjectile(BulletTrajectory& trajectory, BulletConfig& config)
	: Projectile(trajectory, config)
{}

std::vector<std::shared_ptr<EntityCollision>> HomingProjectile::DetectCollisions(std::shared_ptr<CollisionQuadTree> quadTree)
{
	std::vector<std::shared_ptr<EntityCollision>> collisions;

	auto distance = 10.0f;
	auto query = RectangleQuery(sf::FloatRect(
		this->position.x - distance,
		this->position.y - distance,
		this->position.x + distance,
		this->position.y + distance
		));

	quadTree->Query(&query, collisions,
		[this](std::shared_ptr<Entity> target) -> std::shared_ptr<EntityCollision> {
			if (target != this->GetOwner() &&
				target->GetTag() != this->GetOwner()->GetTag())
			{
				// here dont really care if we hit bang on, only that we are close
				return std::make_shared<EntityCollision>(target, this->position);
			}
			return nullptr;
		});

	std::vector<std::shared_ptr<EntityCollision>> fineTuned;
	if (collisions.size())
	{
		// find closest
		auto closest = std::min_element(collisions.begin(), collisions.end(),
			[this](std::shared_ptr<EntityCollision> a, std::shared_ptr<EntityCollision> b) -> bool {
				auto aDist = Dimensions::ManhattanDistance(this->position, a->point);
				auto bDist = Dimensions::ManhattanDistance(this->position, b->point);
				return aDist < bDist;
			});

		// Potential modes identified
		// Evadable
		//this->velocity += normalisedDirection / (0.2f * magnitude);
		// Accurate
		//this->velocity = Dimensions::Normalise(this->velocity + (normalisedDirection / (0.2f * magnitude)));
		// Search and destroy
		//this->velocity = Dimensions::Normalise(this->velocity + (direction / (0.2f * magnitude)));

		// tend towards closest target
		auto direction = (*closest)->target->GetPosition() - this->position;
		auto magnitude = Dimensions::Magnitude(direction);
		auto normalisedDirection = Dimensions::Normalise(direction);
		this->velocity = Dimensions::Normalise(this->velocity + (normalisedDirection / (0.2f * magnitude)));

		for (auto& c : collisions)
		{
			if (c->target->DetectCollision(this->position))
			{
				fineTuned.push_back(std::make_shared<EntityCollision>(c->target, this->position));
				if (!config.penetrating)
				{
					this->spent = true;
				}
			}
		}

	}

	return fineTuned;
}