#include "homing_projectile.h"

#include "util/math_utils.h"

#include "util/i_glow_shader_renderer.h"
#include "entity/entity.h"
#include "util/i_ray_caster.h"

HomingProjectile::HomingProjectile(BulletTrajectory& trajectory, BulletConfig config)
	: Projectile(trajectory, config), mass(1.0f), G(100.0f)
{}

std::vector<EntityCollision> HomingProjectile::DetectCollisions(std::vector<std::shared_ptr<Entity>> targets)
{
	std::vector<EntityCollision> collisions;
	auto closest = this->FindClosest(targets);
	if (closest)
	{
		// tend towards closest target
		auto direction = closest->GetPosition() - this->position;
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

		if(closest->DetectCollision(this->position))
		{
			collisions.push_back(EntityCollision(closest, this->position));

			if (!config.penetrating) {
				this->spent = true;
			}
		}
	}
	return collisions;
}