#include "player_input.h"

Input PlayerInput::SampleInput() {

	Input in;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		in.movement.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		in.movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		in.movement.x = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		in.movement.x = 1;
	}

	in.fire = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		in.fire = true;
	}

	// Just to test gravity
	in.falling = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		in.falling = true;
	}

	return in;
}