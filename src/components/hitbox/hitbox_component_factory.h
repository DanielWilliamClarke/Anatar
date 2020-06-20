#ifndef HITBOX_COMPONENT_FACTORY_H
#define HITBOX_COMPONENT_FACTORY_H
#pragma once

#include "i_hitbox_component_factory.h"
#include "hitbox_component.h"

class HitboxComponentFactory : public IHitboxComponentFactory
{
public:
	HitboxComponentFactory() = default;
	virtual ~HitboxComponentFactory() = default;
	virtual std::shared_ptr<HitboxComponent> CreateInstance() {
		return std::make_shared<HitboxComponent>();
	}
};

#endif //HITBOX_COMPONENT_FACTORY_H