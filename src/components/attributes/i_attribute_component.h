#ifndef I_ATTRBUTE_COMPONENT_H
#define I_ATTRBUTE_COMPONENT_H
#pragma once

class IAttributeComponent
{
public:
	IAttributeComponent() = default;
	virtual ~IAttributeComponent() = default;
	virtual void TakeDamage(float damage) = 0;
	virtual bool IsDead() const = 0;
};

#endif // I_ATTRBUTE_COMPONENT_H
