#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <SFML/Graphics.hpp>

#include "state/state.h"
#include "entity/entity_update.h"

struct Input 
{
	sf::Vector2f movement;
	bool falling{};
    WeaponTriggerState weaponState;
};

class PlayerInput
{
public:
    PlayerInput();

	[[nodiscard]] Input SampleInput();

private:
    void processTrigger (sf::Keyboard::Key key, WeaponSlot slot, bool defaultState = false);

private:
    std::unordered_map<sf::Keyboard::Key, bool> pressed;

    Input input;
};

#endif