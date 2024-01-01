#ifndef I_WEAPON_COMPONENT_FACTORY_H
#define I_WEAPON_COMPONENT_FACTORY_H

#include "i_weapon_component.h"

class IWeaponComponent;
class IBulletSystem;

class IWeaponComponentFactory
{
public:
	IWeaponComponentFactory() = default;
	virtual ~IWeaponComponentFactory() = default;

	[[nodiscard]] virtual std::shared_ptr<IWeaponComponent> Construct(
        const std::shared_ptr<IBulletSystem>& bulletSystem,
        WeaponSlot slot,
        float delay
    ) const = 0;
};

#endif //I_WEAPON_COMPONENT_FACTORY_H