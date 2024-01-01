#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <SFML/Graphics.hpp>

#include "components/weapon/i_weapon_component.h"
#include "state/state.h"

struct Input 
{
	sf::Vector2f movement;
	bool falling{};

    std::unordered_map<WeaponSlot, bool> triggers{};
    bool fire;
};

class PlayerInput
{
public:
    PlayerInput();

	[[nodiscard]] Input SampleInput();

private:
    void processTrigger (sf::Keyboard::Key key, WeaponSlot slot);

private:
    Input input;

    std::unordered_map<sf::Keyboard::Key, bool> pressed;
};

#endif