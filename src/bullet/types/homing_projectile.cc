#include "homing_projectile.h"

#include "util/math_utils.h"

#include "renderer/i_renderer.h"
#include "util/i_ray_caster.h"
#include "quad_tree/shapes.h"
#include "quad_tree/quad_tree.h"
#include "bullet/collision.h"

HomingProjectile::HomingProjectile(BulletTrajectory& trajectory, BulletConfig& config)
	: Projectile(trajectory, config)
{}

void HomingProjectile::Draw(std::shared_ptr<IRenderer> renderer, float interp)
{
	renderer->GetDebugTarget().draw(line.data(), 2, sf::Lines);

	auto rectangle = sf::RectangleShape();
	rectangle.setPosition(sf::Vector2f(this->zone.left, this->zone.top));
	rectangle.setSize(sf::Vector2f(this->zone.width, this->zone.height));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Magenta);
	rectangle.setOutlineThickness(-1.0f);
	renderer->GetDebugTarget().draw(rectangle);

	Projectile::Draw(renderer, interp);
}

std::vector<std::shared_ptr<Collision>> HomingProjectile::DetectCollisions(const std::shared_ptr<QuadTree<Collision, CollisionMediators>>& quadTree)
{
	auto distance = 200.0f;
	this->zone = sf::FloatRect(
		this->position.x - (distance / 2),
		this->position.y - (distance / 2),
		distance,
		distance);
	auto query = RectangleQuery(this->zone);

	std::vector<std::shared_ptr<Collision>> collisions;
	quadTree->Query(&query, collisions,
		[this](std::shared_ptr<Point<CollisionMediators>> point) -> std::shared_ptr<Collision> {
			if (point->tag != this->GetTag() && point->payload->zoneTest(this->zone))
			{
				return std::make_shared<Collision>(this->shared_from_this(), point);
			}
			return nullptr;
		});

	this->line = {};
	std::vector<std::shared_ptr<Collision>> fineTuned;
	if (collisions.size())
	{
		// We want to check all for collisions just in case
		for (auto& c : collisions)
		{
			auto collision = c->target->payload->pointTest(this->position, this->velocity, false);
			if (collision)
			{
				c->collisionPosition = *collision;
				fineTuned.push_back(c);
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
				[this](std::shared_ptr<Collision> a, std::shared_ptr<Collision> b) -> bool {
					auto aDist = Dimensions::ManhattanDistance(this->position, a->target->position);
					auto bDist = Dimensions::ManhattanDistance(this->position, b->target->position);
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
				sf::Vertex(collisions.front()->target->position),
				sf::Vertex(this->position)
			};

			// tend towards closest target
			auto direction = collisions.front()->target->position - this->position;
			auto magnitude = Dimensions::Magnitude(direction);
			auto normalisedDirection = Dimensions::Normalise(direction);
			this->velocity = Dimensions::Normalise(this->velocity + (normalisedDirection / (0.2f * magnitude)));
		}
	}

	return fineTuned;
}