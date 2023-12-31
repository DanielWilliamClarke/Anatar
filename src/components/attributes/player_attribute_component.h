#ifndef PLAYER_ATTRBUTE_COMPONENT_H
#define PLAYER_ATTRBUTE_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <memory>

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
	PlayerAttributeComponent(
        std::shared_ptr<IPlayerHud> hud,
        std::shared_ptr<DamageEffects> damageEffects,
        PlayerAttributeConfig config
    );

    ~PlayerAttributeComponent() override = default;

	void TakeDamage(float damage, sf::Vector2f& impactPoint) override;
    [[nodiscard]] bool IsDead() const override;

	void Update(float dt) override;
	void RegisterKill(float score) override;
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

#endif
