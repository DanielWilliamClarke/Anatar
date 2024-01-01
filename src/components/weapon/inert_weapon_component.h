#ifndef INERT_WEAPON_COMPONENT_H
#define INERT_WEAPON_COMPONENT_H

#include "i_weapon_component.h"

class InertWeaponComponent : public IWeaponComponent
{
public:
    InertWeaponComponent()
        : IWeaponComponent(WeaponSlot::NONE)
    {};
	~InertWeaponComponent() override = default;

	void Fire(sf::Vector2f position, BulletConfig& config) override {};
};

#endif