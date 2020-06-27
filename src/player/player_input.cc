#include "player_input.h"

const Input PlayerInput::SampleInput() const {

	Input in;

	sf::Vector2f movement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x = 1;
	}

	in.movement = movement;

	// Just to test gravity
	in.falling = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		in.falling = true;
	}

	return in;
}