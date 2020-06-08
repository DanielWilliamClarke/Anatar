#pragma once 

#include <SFML/Graphics.hpp>

struct Input 
{
	sf::Vector2f movement;
	bool falling;
};

class PlayerInput
{
public:
	PlayerInput() = default;
	virtual ~PlayerInput() = default;
	const Input SampleInput() const;
};