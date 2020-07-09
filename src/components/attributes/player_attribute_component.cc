#include "player_attribute_component.h"

#include <math.h>
#include <iostream>

#include "../../ui/i_player_hud.h"

PlayerAttributeComponent::PlayerAttributeComponent(std::shared_ptr<IPlayerHud> hud, float health, float shields, float shieldRecharge, float shieldRechargeDelay)
	: hud(hud), health(health), shields(shields), maxHealth(health), maxShields(shields), accumulator(0.0f), shieldRecharge(shieldRecharge), shieldRechargeDelay(shieldRechargeDelay), score(0.0f)
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

	this->hud->Update(this->health, this->maxHealth, this->shields, this->maxShields, this->score);
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