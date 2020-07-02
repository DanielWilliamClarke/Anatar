#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H
#pragma once 

#include <SFML/Graphics.hpp>

struct Input 
{
	sf::Vector2f movement;
	bool falling;
	bool fire;
};

class PlayerInput
{
public:
	PlayerInput() = default;
	virtual ~PlayerInput() = default;
	const Input SampleInput() const;
};

#endif //PLAYER_INPUT_H