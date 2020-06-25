#ifndef I_HITBOX_COMPONENT_FACTORY_H
#define I_HITBOX_COMPONENT_FACTORY_H
#pragma once
#include <memory>

class HitboxComponent;

class IHitboxComponentFactory
{
public:
	IHitboxComponentFactory() = default;
	virtual ~IHitboxComponentFactory() = default;
	virtual std::shared_ptr<HitboxComponent> CreateInstance() const = 0;
};

#endif //I_HITBOX_COMPONENT_FACTORY_H