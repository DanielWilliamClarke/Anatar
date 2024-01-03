#ifndef SINGLE_BEAM_WEAPON_COMPONENT_FACTORY_H
#define SINGLE_BEAM_WEAPON_COMPONENT_FACTORY_H

#include "components/weapon/i_weapon_component_factory.h"
#include "bullet/i_bullet_factory.h"

#include "single_beam_weapon_component.h"

class SingleBeamWeaponComponentFactory: public IWeaponComponentFactory
{
public:
	SingleBeamWeaponComponentFactory(std::shared_ptr<IBulletFactory> factory, float duration, float coolDown)
		: factory(factory),
		duration(duration),
        coolDown(coolDown)
	{}

	~SingleBeamWeaponComponentFactory() override = default;

    [[nodiscard]] std::shared_ptr<IWeaponComponent> Construct(
        const std::shared_ptr<IBulletSystem>& bulletSystem,
        const std::shared_ptr<IPlayerHud>& hud,
        WeaponSlot slot,
        float delay
    ) const override {
        auto component = std::make_shared<SingleBeamWeaponComponent>(duration, coolDown);

        component->setBulletSystem(bulletSystem);
        component->setBulletFactory(factory);
        component->setHud(hud);
        component->setSlot(slot);

        return component;
	};

private:
	std::shared_ptr<IBulletFactory> factory;
	float duration;
	float coolDown;
};

#endif