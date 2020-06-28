#ifndef I_PLAYER_MOVEMENT_COMPONENT_H
#define I_PLAYER_MOVEMENT_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "i_global_movement_component.h"

struct Input;

class IPlayerMovementComponent : public IGlobalMovementComponent
{
public:
	virtual sf::Vector2f Integrate(Input& in, const float& dt) = 0;
};

#endif // I_PLAYER_MOVEMENT_COMPONENT_H