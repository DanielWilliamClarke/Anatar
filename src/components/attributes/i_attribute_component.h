#ifndef I_ATTRBUTE_COMPONENT_H
#define I_ATTRBUTE_COMPONENT_H


#include <SFML/Graphics.hpp>
#include <memory>

struct BulletConfig;
class IWeaponComponent;

struct DamageEffects
{
	std::shared_ptr<IWeaponComponent> generator;
	std::shared_ptr<BulletConfig> death;
	std::shared_ptr<BulletConfig> health;
	std::shared_ptr<BulletConfig> shield;

	DamageEffects(std::shared_ptr<IWeaponComponent> generator, std::shared_ptr<BulletConfig> death, std::shared_ptr<BulletConfig> health, std::shared_ptr<BulletConfig> shield)
		: generator(generator), death(death), health(health), shield(shield)
	{}
};

class IAttributeComponent
{
public:
	IAttributeComponent() = default;
	virtual ~IAttributeComponent() = default;
	virtual void TakeDamage(float damage, sf::Vector2f& impactPoint) = 0;
	virtual bool IsDead() const = 0;
	virtual void RegisterKill(float score) = 0;
};

#endif // I_ATTRBUTE_COMPONENT_H
