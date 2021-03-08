#ifndef ENTITY_UPDATE_H
#define ENTITY_UPDATE_H
#pragma once

#include <SFML/Graphics.hpp>

struct BulletConfig;

struct EntityUpdate 
{
	sf::Vector2f position;
	int direction;
	bool loop;
	bool fire;
	std::shared_ptr<BulletConfig> bulletConfig;

	EntityUpdate() = default;
	EntityUpdate(sf::Vector2f position,
		int direction,
		std::shared_ptr<BulletConfig> bulletConfig,
		bool fire = true,
		bool loop = true)
		: position(position), direction(direction), bulletConfig(bulletConfig), fire(fire), loop(loop)
	{}
};

#endif //ENTITY_UPDATE_H