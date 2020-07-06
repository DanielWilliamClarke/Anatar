#include "health_attribute_component.h"

#include <math.h>

HealthAttributeComponent::HealthAttributeComponent(float health, float shields)
	: health(health), shields(shields), maxHealth(health), maxShields(shields)
{}

void HealthAttributeComponent::TakeDamage(float damage)
{
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

bool HealthAttributeComponent::IsDead() const
{
	return this->health <= 0;
}