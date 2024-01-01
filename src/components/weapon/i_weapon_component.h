#ifndef I_WEAPON_COMPONENT_H
#define I_WEAPON_COMPONENT_H

#include <SFML/Graphics.hpp>

struct BulletConfig;

enum WeaponSlot : unsigned int {
    NONE = 999,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
};

class IWeaponComponent
{
public:
	explicit IWeaponComponent(WeaponSlot slot)
        : slot(slot)
    {}

	virtual ~IWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position, BulletConfig& config) = 0;
	virtual void Cease() {};

    [[ nodiscard ]] virtual WeaponSlot getSlot() const
    {
        return this->slot;
    }
protected:
    WeaponSlot slot;
};

#endif