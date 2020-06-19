#pragma once
#include <SFML/Graphics.hpp>

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;

	EntityUpdate() = default;
	EntityUpdate(sf::Vector2f position, int direction, bool loop = true)
		: position(position), direction(direction), loop(loop)
	{}
};
