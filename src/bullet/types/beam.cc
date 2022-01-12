#include "beam.h"

#include "util/math_utils.h"

#include "renderer/i_renderer.h"
#include "util/i_ray_caster.h"
#include "quad_tree/quad_tree.h"
#include "bullet/collision.h"

Beam::Beam(BulletTrajectory& trajectory, BulletConfig& config, std::shared_ptr<IRayCaster> rayCaster, sf::FloatRect bounds, float damageRate)
	: Bullet(trajectory, config),
	rayCaster(rayCaster),
	round(std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 5.0f))),
	collisionPosition(std::shared_ptr<sf::Vector2f>(nullptr)),
	bounds(bounds),
	damageRateAccumulator(0.0f),
	damageRate(damageRate),
	damageCache(config.damage)
{
	this->round->setFillColor(config.color);
	auto roundBounds = this->round->getLocalBounds();
	this->round->setOrigin(0, roundBounds.height / 2.0f);
	this->round->setRotation(AngleConversion::ToDegrees(atan2(this->velocity.y, this->velocity.x)));
}

void Beam::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position = this->config.callbacks.ownerPositionSampler();

	this->round->setPosition(this->position);

	auto beamEnd = collisionPosition ?
		*collisionPosition :
		this->rayCaster->RayBoxIntersects(this->position, this->velocity, bounds)->point;

	this->round->setSize(
		sf::Vector2f(
			Dimensions::DistanceBetween(this->position, beamEnd),
			this->round->getSize().y));

	config.damage = 0;
	this->damageRateAccumulator += dt;
	if (this->damageRateAccumulator >= this->damageRate)
	{
 		config.damage = damageCache;
		this->damageRateAccumulator = 0;
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

void Beam::Draw(std::shared_ptr<IRenderer> renderer, float interp)
{
   	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->GetTarget().draw(*round);
	renderer->AddGlow(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);

	if (collisionPosition) {
		renderer->AddGlow(*collisionPosition, this->round->getFillColor(), config.glowAttenuation);
	}
}

std::vector<std::shared_ptr<Collision>> Beam::DetectCollisions(std::shared_ptr<QuadTree<Collision>> quadTree)
{
	// Clear collision point before detection
	collisionPosition = nullptr;

	std::vector<std::shared_ptr<Collision>> collisions;
	auto query = RayQuery(rayCaster, this->position, this->velocity);
	quadTree->Query(&query, collisions,
		[this](std::shared_ptr<Point> point) -> std::shared_ptr<Collision> {
			if (point->tag != this->GetTag())
			{
				auto collision = point->collisionTest(this->position, this->velocity, true);
				if (collision) {
					return std::make_shared<Collision>(this->shared_from_this(), point, *collision);
				}
			}		
			return nullptr;
		});

	if (collisions.size() > 1)
	{
		std::sort(collisions.begin(), collisions.end(),
			[this](std::shared_ptr<Collision> a, std::shared_ptr<Collision> b) -> bool {
				auto aDist = Dimensions::ManhattanDistance(this->position, a->collisionPosition);
				auto bDist = Dimensions::ManhattanDistance(this->position, b->collisionPosition);
				return aDist < bDist;
			});
	}

	// Set collision point to hit the first entity if the beam cant penetrate
	if (!config.penetrating && collisions.size())
	{
		collisionPosition = std::make_shared<sf::Vector2f>(collisions.front()->collisionPosition);
		collisions = { collisions.front() };
	}

	return collisions;
}

void Beam::Reignite()
{
	this->accumulator = 0;
}

void Beam::Cease()
{
	this->spent = true;
}