#ifndef I_WEAPON_COMPONENT_H
#define I_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>

struct BulletConfig;
class IPlayerHud;

enum WeaponSlot : unsigned int {
    NONE = 999,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
};

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
{
public:
    IWeaponComponent(
        std::shared_ptr<IPlayerHud> hud,
        WeaponSlot slot
    );

	virtual ~IWeaponComponent() = default;

    [[nodiscard]] virtual WeaponState getWeaponState() const = 0;
    [[nodiscard]] virtual WeaponSlot getSlot() const;

    virtual void Fire(sf::Vector2f position, BulletConfig& config) = 0;
    void Update(WeaponTriggerState& triggerState);
    virtual void Cease();

protected:
    std::shared_ptr<IPlayerHud> hud;
    WeaponSlot slot;
};

#endif