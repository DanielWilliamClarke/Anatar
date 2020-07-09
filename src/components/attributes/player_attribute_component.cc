#include "player_attribute_component.h"

#include <math.h>
#include <iostream>

PlayerAttributeComponent::PlayerAttributeComponent(float health, float shields, float shieldRecharge, float shieldRechargeDelay)
	: health(health), shields(shields), maxHealth(health), maxShields(shields), accumulator(0.0f), shieldRecharge(shieldRecharge), shieldRechargeDelay(shieldRechargeDelay), score(0.0f)
{}

void PlayerAttributeComponent::Update(float dt)
{
	this->accumulator += this->clock.restart().asSeconds();
	if (this->accumulator >= this->shieldRechargeDelay && 
		this->shields < this->maxShields)
	{
		auto shieldRechargeIncremenet = this->shieldRecharge * dt;
		if (this->maxShields < shieldRechargeIncremenet + this->shields)
		{
			this->shields = this->maxShields;
		}
		else
		{
			this->shields += shieldRechargeIncremenet;
		}
	}

	std::cout << "Sheilds " << std::to_string(this->shields) << std::endl;
	std::cout << "Health " << std::to_string(this->health) << std::endl;
	std::cout << "Score " << std::to_string(this->score) << std::endl;
}

void PlayerAttributeComponent::Draw(sf::RenderTarget& target) const
{
}

void PlayerAttributeComponent::RegisterKill(float score)
{
	this->score += score;
}

void PlayerAttributeComponent::TakeDamage(float damage)
{
	this->accumulator = 0;

	if (this->shields > damage)
	{
		this->shields -= damage;
		return;
	}

	auto throughDamange = damage - this->shields;
	if (this->shields > 0)
	{
		this->shields -= damage - throughDamange;
	}

	if (this->health < throughDamange)
	{
		this->health -= throughDamange - (throughDamange - this->health);
		return;
	}
	this->health -= throughDamange;
}

bool PlayerAttributeComponent::IsDead() const
{
	return this->health <= 0;
}