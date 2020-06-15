#include "player_input.h"

const Input PlayerInput::SampleInput() const {

	Input in;

	sf::Vector2f movement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.x = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.x = 1;
	}

	in.movement = movement;

	// Just to test gravity
	in.falling = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		in.falling = true;
	}

	return in;
}