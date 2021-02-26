#include "beam.h"

#include "../entity/entity.h"
#include "../util/i_glow_shader_renderer.h"

Beam::Beam(sf::Vector2f position, sf::Vector2f velocity, BulletConfig config)
	: Bullet(position, velocity, config), round(std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 2.0f)))
{
}

void Beam::Update(float dt, float worldSpeed)
{
	this->lastPosition = this->position;
	this->position = this->config.owner->GetPosition();
	this->round->setPosition(this->position);

	this->round->setSize(
		sf::Vector2f(
			this->config.owner->DistanceTo(this->collisionPosition),
			2.0f));
}

void Beam::Draw(std::shared_ptr<IGlowShaderRenderer> renderer, float interp)
{
	this->round->setPosition(position * interp + lastPosition * (1.0f - interp));
	renderer->ExposeTarget().draw(*round);
	renderer->AddGlowAtPosition(this->round->getPosition(), this->round->getFillColor(), config.glowAttenuation);
}


void Beam::CollisionDetected(sf::Vector2f point)
{
	spent = config.penetrating ? false : true;
}

std::shared_ptr<sf::Shape> Beam::GetRound() const
{
	return round;
}