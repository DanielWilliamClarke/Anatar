#pragma once
#include <SFML/Graphics.hpp>

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;

	EntityUpdate() = default;
	EntityUpdate(sf::Vector2f position, int direction)
		: position(position), direction(direction)
	{}
};
