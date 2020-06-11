#pragma once
#include <SFML/Graphics.hpp>

struct EntityUpdate 
{
	sf::Vector2f newPosition;
	const int direction;

	EntityUpdate(sf::Vector2f newPosition, const int direction)
		: newPosition(newPosition), direction(direction)
	{}
};
