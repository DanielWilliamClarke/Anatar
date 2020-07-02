#ifndef ENTITY_UPDATE_H
#define ENTITY_UPDATE_H
#pragma once

#include <SFML/Graphics.hpp>

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;
	bool fire;

	EntityUpdate() = default;
	EntityUpdate(sf::Vector2f position, int direction, bool fire = true, bool loop = true)
		: position(position), direction(direction), fire(fire), loop(loop)
	{}
};

#endif //ENTITY_UPDATE_H