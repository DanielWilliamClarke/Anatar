#ifndef I_ATTRBUTE_COMPONENT_H
#define I_ATTRBUTE_COMPONENT_H
#pragma once

#include <SFML/Graphics.hpp>

class IAttributeComponent
{
public:
	IAttributeComponent() = default;
	virtual ~IAttributeComponent() = default;
	virtual void TakeDamage(float damage, sf::Vector2f& impactPoint) = 0;
	virtual bool IsDead() const = 0;
	virtual void RegisterKill(float score) = 0;
};

#endif // I_ATTRBUTE_COMPONENT_H
