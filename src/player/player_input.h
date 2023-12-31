#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <SFML/Graphics.hpp>

struct Input 
{
	sf::Vector2f movement;
	bool falling{};
	bool fire{};
};

class PlayerInput
{
public:
	[[nodiscard]] static Input SampleInput() ;
};

#endif