#ifndef PLAYER_ATTRBUTE_COMPONENT_H
#define PLAYER_ATTRBUTE_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>
#include "i_player_attribute_component.h"

class IPlayerHud;

struct PlayerAttributeConfig
{
	float health;
	float shields;
	float shieldRecharge;
	float shieldRechargeDelay;

	PlayerAttributeConfig(float health, float shields, float shieldRecharge, float shieldRechargeDelay)
		: health(health), shields(shields), shieldRecharge(shieldRecharge), shieldRechargeDelay(shieldRechargeDelay) 
	{}
};

class PlayerAttributeComponent : public IPlayerAttributeComponent
{
public:
	PlayerAttributeComponent(std::shared_ptr<IPlayerHud> hud, std::shared_ptr<DamageEffects> damageEffects, PlayerAttributeConfig config);
	virtual ~PlayerAttributeComponent() = default;

	virtual void TakeDamage(float damage, sf::Vector2f& impactPoint) override;
	virtual bool IsDead() const override;

	virtual void Update(float dt) override;
	virtual void RegisterKill(float score) override;

private:

	std::shared_ptr<IPlayerHud> hud;
	std::shared_ptr<DamageEffects> damageEffects;

	float maxHealth;
	float health;
	float maxShields;
	float shields;

	float score;

	float accumulator;
	float shieldRecharge;
	float shieldRechargeDelay;
};

#endif //PLAYER_ATTRBUTE_COMPONENT_H
