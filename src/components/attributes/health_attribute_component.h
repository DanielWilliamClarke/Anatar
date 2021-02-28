#ifndef HEALTH_ATTRBUTE_COMPONENT_H
#define HEALTH_ATTRBUTE_COMPONENT_H
#pragma once

#include "i_attribute_component.h"

class HealthAttributeComponent: public IAttributeComponent
{
public:
	HealthAttributeComponent(std::shared_ptr<DamageEffects> damageEffects, float health);
	virtual ~HealthAttributeComponent() = default;

	virtual void TakeDamage(float damage, sf::Vector2f& impactPoint) override;
	virtual bool IsDead() const override;
	virtual void RegisterKill(float score) override {};
private:
	std::shared_ptr<DamageEffects> damageEffects;
	float maxHealth;
	float health;
};

#endif //HEALTH_ATTRBUTE_COMPONENT_H
