#ifndef ENTITY_UPDATE_H
#define ENTITY_UPDATE_H

#include <SFML/Graphics.hpp>
#include "components/weapon/i_weapon_component.h"

struct BulletConfig;
struct Input;

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;
    WeaponTriggerState& weaponState;
	BulletConfig& bulletConfig;

	EntityUpdate(sf::Vector2f position,
		int direction,
		BulletConfig& bulletConfig,
        WeaponTriggerState& weaponState,
		bool loop = true
    )
		: position(position), direction(direction), bulletConfig(bulletConfig), weaponState(weaponState), loop(loop)
	{}
};

#endif