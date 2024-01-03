#ifndef RANDOM_SHOT_WEAPON_COMPONENT_FACTORY_H
#define RANDOM_SHOT_WEAPON_COMPONENT_FACTORY_H

#include "components/weapon/i_weapon_component_factory.h"
#include "bullet/i_bullet_factory.h"
#include "util/i_random_number_source.h"

#include "random_shot_weapon_component.h"

class RandomShotWeaponComponentFactory: public IWeaponComponentFactory
{
public:
	RandomShotWeaponComponentFactory(
        std::shared_ptr<IBulletFactory> factory,
        std::shared_ptr<IRandomNumberSource<int>> randSource,
        float numBullets
    )
		: factory(factory),
          randSource(randSource),
		  numBullets(numBullets)
	{}

	~RandomShotWeaponComponentFactory() override = default;

    [[nodiscard]] std::shared_ptr<IWeaponComponent> Construct(
        const std::shared_ptr<IBulletSystem>&  bulletSystem,
        const std::shared_ptr<IPlayerHud>& hud,
        WeaponSlot slot,
        float delay
    ) const override {
        auto component = std::make_shared<RandomShotWeaponComponent>(randSource, numBullets);

        component->setBulletSystem(bulletSystem);
        component->setBulletFactory(factory);
        component->setHud(hud);
        component->setSlot(slot);

        return component;
	};

private:
	std::shared_ptr<IBulletFactory> factory;
    std::shared_ptr<IRandomNumberSource<int>> randSource;
	float numBullets;
};

#endif