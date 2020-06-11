#pragma once

#include "i_hitbox_component_factory.h"
#include "../components/hitbox_component.h"

class HitboxComponentFactory : public IHitboxComponentFactory
{
public:
	HitboxComponentFactory() = default;
	virtual ~HitboxComponentFactory() = default;
	virtual std::shared_ptr<HitboxComponent> CreateInstance() {
		return std::make_shared<HitboxComponent>();
	}
};