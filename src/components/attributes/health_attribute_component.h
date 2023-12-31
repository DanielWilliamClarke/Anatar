#ifndef HEALTH_ATTRBUTE_COMPONENT_H
#define HEALTH_ATTRBUTE_COMPONENT_H


#include <memory>

#include "i_attribute_component.h"

class HealthAttributeComponent: public IAttributeComponent
{
public:
	HealthAttributeComponent(std::shared_ptr<DamageEffects> damageEffects, float health);
	~HealthAttributeComponent() override = default;

	void TakeDamage(float damage, sf::Vector2f& impactPoint) override;
    [[nodiscard]] bool IsDead() const override;
	void RegisterKill(float score) override {};
private:
	std::shared_ptr<DamageEffects> damageEffects;
	float maxHealth;
	float health;
};

#endif
