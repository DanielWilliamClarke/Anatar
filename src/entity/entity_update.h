#ifndef ENTITY_UPDATE_H
#define ENTITY_UPDATE_H

#include <SFML/Graphics.hpp>

struct BulletConfig;
struct Input;

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;
	Input& input;
	BulletConfig& bulletConfig;

	EntityUpdate(sf::Vector2f position,
		int direction,
		BulletConfig& bulletConfig,
        Input& input,
		bool loop = true
    )
		: position(position), direction(direction), bulletConfig(bulletConfig), input(input), loop(loop)
	{}
};

#endif