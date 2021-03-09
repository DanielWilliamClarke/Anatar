#include "homing_projectile.h"

#include "util/math_utils.h"

#include "util/i_glow_shader_renderer.h"
#include "entity/entity.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"

HomingProjectile::HomingProjectile(BulletTrajectory& trajectory, BulletConfig& config)
	: Projectile(trajectory, config)
{}

void HomingProjectile::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	renderer->ExposeTarget().draw(line.data(), 2, sf::Lines);

	auto rectangle = sf::RectangleShape();
	rectangle.setPosition(sf::Vector2f(this->zone.left, this->zone.top));
	rectangle.setSize(sf::Vector2f(this->zone.width, this->zone.height));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Magenta);
	rectangle.setOutlineThickness(-1.0f);
	renderer->ExposeTarget().draw(rectangle);

	Projectile::Draw(renderer, interp);
}

std::vector<std::shared_ptr<EntityCollision>> HomingProjectile::DetectCollisions(std::shared_ptr<CollisionQuadTree> quadTree)
{
	auto distance = 200.0f;
	zone = sf::FloatRect(
		this->position.x - (distance / 2),
		this->position.y - (distance / 2),
		distance,
		distance);
	auto query = RectangleQuery(zone);

	std::vector<std::shared_ptr<EntityCollision>> collisions;
	quadTree->Query(&query, collisions,
		[this](std::shared_ptr<Entity> target) -> std::shared_ptr<EntityCollision> {
			if (target != this->GetOwner() &&
				target->GetTag() != this->GetOwner()->GetTag() &&
				target->IsInside(zone))
			{
				// only want entities that are inside the zone 
				return std::make_shared<EntityCollision>(target, this->position);
			}
			return nullptr;
		});

	this->line = {};
	std::vector<std::shared_ptr<EntityCollision>> fineTuned;
	if (collisions.size())
	{
		// We want to check all for collisions just in case
		for (auto& c : collisions)
		{
			if (c->target->DetectCollision(this->position))
			{
				fineTuned.push_back(std::make_shared<EntityCollision>(c->target, this->position));
				if (!config.penetrating)
				{
					this->spent = true;
					break;
				}
			}
		}

		if (!this->spent)
		{
			// find closest
			std::sort(collisions.begin(), collisions.end(),
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

			// Debug line for testing
			this->line = {
				sf::Vertex(collisions.front()->target->GetPosition()),
				sf::Vertex(this->position)
			};

			// tend towards closest target
			auto direction = collisions.front()->target->GetPosition() - this->position;
			auto magnitude = Dimensions::Magnitude(direction);
			auto normalisedDirection = Dimensions::Normalise(direction);
			this->velocity = Dimensions::Normalise(this->velocity + (normalisedDirection / (0.2f * magnitude)));
		}
	}

	return fineTuned;
}