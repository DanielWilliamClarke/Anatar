#ifndef I_WEAPON_COMPONENT_FACTORY_H
#define I_WEAPON_COMPONENT_FACTORY_H


class IWeaponComponent;
class IBulletSystem;

class IWeaponComponentFactory
{
public:
	IWeaponComponentFactory() = default;
	virtual ~IWeaponComponentFactory() = default;

	virtual std::shared_ptr<IWeaponComponent> Construct(std::shared_ptr<IBulletSystem> bulletSystem, float delay) const = 0;
};

#endif //I_WEAPON_COMPONENT_FACTORY_H