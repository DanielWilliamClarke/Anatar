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
	// sort elements closest to furthest
	std::sort(targets.begin(), targets.end(),
		[this](EntityCollision collisionA, EntityCollision collisionB) -> bool {
			auto distanceA = Dimensions::ManhattanDistance(collisionA.target->GetPosition(), this->position);
			auto distanceB = Dimensions::ManhattanDistance(collisionB.target->GetPosition(), this->position);
			return distanceA < distanceB;
		});

	// Home in on closest target
	if (targets.size()) 
	{
		auto direction = targets.front()->GetPosition() - this->position;
		auto magnitude = 0.05f * Dimensions::Magnitude(direction);
		auto normalisedDirection = Dimensions::Normalise(direction);
		this->velocity += normalisedDirection / magnitude;
	}

	std::vector<std::shared_ptr<Entity>> culledTargets;
	std::copy_if(targets.begin(), targets.end(), std::back_inserter(culledTargets),
		[this](std::shared_ptr<Entity> entity) -> bool {
			return entity->DetectCollisionWithRay(this->position, this->velocity)->intersects;
		});

	std::vector<EntityCollision> collisions;
	if (culledTargets.size() && culledTargets.front()->DetectCollision(this->position))
	{
		// Even if the projectile is penetrating, it can only hit one target at a time
		collisions.push_back(EntityCollision(culledTargets.front(), this->position));
		if (!config.penetrating) {
			this->spent = true;
		}
	}

	return collisions;
}