#ifndef INERT_WEAPON_COMPONENT_H
#define INERT_WEAPON_COMPONENT_H
#pragma once

#include "i_weapon_component.h"

class InertWeaponComponent : public IWeaponComponent
{
public:
	InertWeaponComponent() = default;
	virtual ~InertWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position) override {};

private:
};

#endif //INERT_WEAPON_COMPONENT_H