#ifndef INERT_WEAPON_COMPONENT_H
#define INERT_WEAPON_COMPONENT_H

#include "i_weapon_component.h"

class InertWeaponComponent : public IWeaponComponent
{
public:
    InertWeaponComponent() = default;
	~InertWeaponComponent() override = default;

	void Fire(sf::Vector2f position, BulletConfig& config) override {};
    [[nodiscard]] WeaponState getWeaponState() const override {
        return {
            "Inert",
            100.0,
            0.0,
            false
        };
    }
};

#endif