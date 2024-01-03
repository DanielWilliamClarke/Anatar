#ifndef I_WEAPON_COMPONENT_H
#define I_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "components/weapon/accessors/weapon_accessors.h"

struct BulletConfig;

struct WeaponTriggerState
{
    std::unordered_map<WeaponSlot, bool> triggers{};
    bool fire;
};

struct WeaponState
{
    std::string type;
    float cooldown;
    float accumulator;
    bool canFire;
};

class IWeaponComponent
    : public WeaponHudAccess,
      public WeaponSlotAccess
{
public:
	virtual ~IWeaponComponent() = default;

    [[nodiscard]] virtual WeaponState getWeaponState() const = 0;
    [[nodiscard]] virtual WeaponSlot getSlot() const;

    virtual void Fire(sf::Vector2f position, BulletConfig& config) = 0;
    void Update(WeaponTriggerState& triggerState);
    virtual void Cease();
};

#endif