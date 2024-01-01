#include "player_input.h"

PlayerInput::PlayerInput()
    : input(Input())
{}

Input PlayerInput::SampleInput()
{
    this->input.movement.x = 0;
    this->input.movement.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->input.movement.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
        this->input.movement.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
        this->input.movement.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
        this->input.movement.x = 1;
	}

    this->input.weaponState.fire = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->input.weaponState.fire = true;
    }

    // process triggers
    this->processTrigger(sf::Keyboard::Num1, WeaponSlot::ONE);
    this->processTrigger(sf::Keyboard::Num2, WeaponSlot::TWO);
    this->processTrigger(sf::Keyboard::Num3, WeaponSlot::THREE);
    this->processTrigger(sf::Keyboard::Num4, WeaponSlot::FOUR);

	// Just to test gravity
    this->input.falling = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
        this->input.falling = true;
	}

	return this->input;
}

void PlayerInput::processTrigger (sf::Keyboard::Key key, WeaponSlot slot)
{
    // check if key is pressed
    if(!this->pressed.contains(key))
    {
        this->pressed.insert({key, false});
    }

    // we detect a release event state: t1: on -> t2: off
    auto previousKeyState = this->pressed.at(key);
    auto newKeyState = sf::Keyboard::isKeyPressed(key);
    if (previousKeyState && !newKeyState)
    {
        // key has been released
        if (!this->input.weaponState.triggers.contains(slot))
        {
            this->input.weaponState.triggers.insert({slot, false});
        }

        this->input.weaponState.triggers[slot] = !this->input.weaponState.triggers[slot];
    }

    // set new key state
    this->pressed[key] = newKeyState;
}