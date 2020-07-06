#ifndef HEALTH_ATTRBUTE_COMPONENT_H
#define HEALTH_ATTRBUTE_COMPONENT_H
#pragma once

#include "i_attribute_component.h"

class HealthAttributeComponent: public IAttributeComponent
{
public:
	HealthAttributeComponent(float health, float shields);
	virtual ~HealthAttributeComponent() = default;

	virtual void TakeDamage(float damage) override;

	virtual bool IsDead() const override;

private:

	float maxHealth;
	float health;
	float maxShields;
	float shields;
};

#endif //HEALTH_ATTRBUTE_COMPONENT_H
