#include "player_attribute_component.h"

#include <math.h>
#include <iostream>

#include "../../ui/i_player_hud.h"
#include "components/weapon/i_weapon_component.h"
#include "bullet/bullet.h"

PlayerAttributeComponent::PlayerAttributeComponent(std::shared_ptr<IPlayerHud> hud, std::shared_ptr<DamageEffects> damageEffects, PlayerAttributeConfig config)
	: hud(hud),
	damageEffects(damageEffects),
	health(config.health),
	shields(config.shields),
	maxHealth(config.health),
	maxShields(config.shields),
	accumulator(0.0f),
	shieldRecharge(config.shieldRecharge),
	shieldRechargeDelay(config.shieldRechargeDelay),
	score(0.0f)
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

void PlayerAttributeComponent::TakeDamage(float damage, sf::Vector2f& impactPoint)
{
	this->accumulator = 0;

	if (this->shields > damage)
	{
		this->shields -= damage;
		damageEffects->generator->Fire(impactPoint, *damageEffects->shield);
	}
	else
	{
		auto throughDamange = damage - this->shields;
		if (this->shields > 0)
		{
			// Ensures shields does not go below 0
			this->shields -= damage - throughDamange;
		}

		if (this->health > throughDamange)
		{
			this->health -= throughDamange;
			damageEffects->generator->Fire(impactPoint, *damageEffects->health);
		}
		else 
		{
			// Ensures health does not go below 0
			this->health -= throughDamange - (throughDamange - this->health);
			damageEffects->generator->Fire(impactPoint, *damageEffects->death);
		}
	}
}

bool PlayerAttributeComponent::IsDead() const
{
	return this->health <= 0;
}