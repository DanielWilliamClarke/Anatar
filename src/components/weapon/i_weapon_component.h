#ifndef I_WEAPON_COMPONENT_H
#define I_WEAPON_COMPONENT_H
#pragma once

class IWeaponComponent
{
public:
	IWeaponComponent() = default;
	virtual ~IWeaponComponent() = default;

	virtual void Fire(sf::Vector2f position) = 0;
};

#endif //I_WEAPON_COMPONENT_H