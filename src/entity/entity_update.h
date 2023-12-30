#ifndef ENTITY_UPDATE_H
#define ENTITY_UPDATE_H


#include <SFML/Graphics.hpp>

struct BulletConfig;

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;
	bool fire;
	BulletConfig& bulletConfig;

	EntityUpdate() = default;
	EntityUpdate(sf::Vector2f position,
		int direction,
		BulletConfig& bulletConfig,
		bool fire = true,
		bool loop = true)
		: position(position), direction(direction), bulletConfig(bulletConfig), fire(fire), loop(loop)
	{}
};

#endif //ENTITY_UPDATE_H