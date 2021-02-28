#include "health_attribute_component.h"

#include <math.h>

HealthAttributeComponent::HealthAttributeComponent(float health)
	: health(health), maxHealth(health)
{}

void HealthAttributeComponent::TakeDamage(float damage, sf::Vector2f& impactPoint)
{
	if (this->health < damage)
	{
		this->health -= damage - (damage - this->health);
		return;
	}
	this->health -= damage;
}

bool HealthAttributeComponent::IsDead() const
{
	return this->health <= 0;
}