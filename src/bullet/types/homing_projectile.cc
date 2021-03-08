#include "homing_projectile.h"

#include "util/math_utils.h"

#include "util/i_glow_shader_renderer.h"
#include "entity/entity.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"

HomingProjectile::HomingProjectile(BulletTrajectory& trajectory, BulletConfig& config)
	: Projectile(trajectory, config)
{}

std::vector<EntityCollision> HomingProjectile::DetectCollisions(std::shared_ptr<QuadTree<std::shared_ptr<Entity>>> quadTree)
{
	auto query = CircleQuery(this->position, 2.5f);
	auto closest = quadTree->Closest(this->position, &query, [this](std::shared_ptr<Entity> target) -> bool {
		return target != this->GetOwner() &&
			target->GetTag() != this->GetOwner()->GetTag();
		});

	std::vector<EntityCollision> collisions;
	if (closest.size())
	{
		// tend towards closest target
		auto direction = closest.front().data->GetPosition() - this->position;
		auto magnitude = Dimensions::Magnitude(direction);
		auto normalisedDirection = Dimensions::Normalise(direction);
		this->velocity = Dimensions::Normalise(this->velocity + (normalisedDirection / (0.2f * magnitude)));

		// Potential modes identified
		// Evadable
		//this->velocity += normalisedDirection / (0.2f * magnitude);
		// Accurate
		//this->velocity = Dimensions::Normalise(this->velocity + (normalisedDirection / (0.2f * magnitude)));
		// Search and destroy
		//this->velocity = Dimensions::Normalise(this->velocity + (direction / (0.2f * magnitude)));

		if(closest.front().data->DetectCollision(this->position))
		{
			collisions.push_back(EntityCollision(closest.front().data, this->position));

			if (!config.penetrating) {
				this->spent = true;
			}
		}
	}
	return collisions;
}