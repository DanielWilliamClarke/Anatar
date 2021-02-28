#include "health_attribute_component.h"

#include <math.h>

#include "components/weapon/i_weapon_component.h"
#include "bullet/bullet.h"

HealthAttributeComponent::HealthAttributeComponent(std::shared_ptr<DamageEffects> damageEffects, float health)
	: damageEffects(damageEffects), health(health), maxHealth(health)
{}

void HealthAttributeComponent::TakeDamage(float damage, sf::Vector2f& impactPoint)
{
	if (this->health < damage)
	{
		this->health -= damage - (damage - this->health);
		damageEffects->generator->Fire(impactPoint, *damageEffects->death);
	}
	else 
	{
		this->health -= damage;
		damageEffects->generator->Fire(impactPoint, *damageEffects->health);
	}
}

bool HealthAttributeComponent::IsDead() const
{
	return this->health <= 0;
}