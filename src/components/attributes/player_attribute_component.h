#ifndef PLAYER_ATTRBUTE_COMPONENT_H
#define PLAYER_ATTRBUTE_COMPONENT_H
#pragma once

#include "i_player_attribute_component.h"

class IPlayerHud;

class PlayerAttributeComponent : public IPlayerAttributeComponent
{
public:
	PlayerAttributeComponent(std::shared_ptr<IPlayerHud> hud, float health, float shields, float shieldRecharge, float shieldRechargeDelay);
	virtual ~PlayerAttributeComponent() = default;

	virtual void TakeDamage(float damage) override;
	virtual bool IsDead() const override;

	virtual void Update(float dt) override;
	virtual void RegisterKill(float score) override;

private:

	std::shared_ptr<IPlayerHud> hud;

	float maxHealth;
	float health;
	float maxShields;
	float shields;

	float score;

	sf::Clock clock;
	float accumulator;
	float shieldRecharge;
	float shieldRechargeDelay;
};

#endif //PLAYER_ATTRBUTE_COMPONENT_H
