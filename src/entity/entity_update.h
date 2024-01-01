#ifndef ENTITY_UPDATE_H
#define ENTITY_UPDATE_H

#include <SFML/Graphics.hpp>
#include "components/weapon/i_weapon_component.h"

struct BulletConfig;
struct Input;

struct WeaponStateConfig
{
    std::unordered_map<WeaponSlot, bool> triggers{};
    bool fire;
};

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;
    WeaponStateConfig& weaponState;
	BulletConfig& bulletConfig;

	EntityUpdate(sf::Vector2f position,
		int direction,
		BulletConfig& bulletConfig,
        WeaponStateConfig& weaponState,
		bool loop = true
    )
		: position(position), direction(direction), bulletConfig(bulletConfig), weaponState(weaponState), loop(loop)
	{}
};

#endif