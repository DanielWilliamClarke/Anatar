#ifndef ANIMATION_COMPONENT_FACTORY_H
#define ANIMATION_COMPONENT_FACTORY_H
#pragma once

#include "i_animation_component_factory.h"
#include "animation_component.h"

class AnimationComponentFactory : public IAnimationComponentFactory
{
public:
	AnimationComponentFactory() = default;
	virtual ~AnimationComponentFactory() = default;
	virtual std::shared_ptr<AnimationComponent> CreateInstance() const override {
		return std::make_shared<AnimationComponent>();
	}
};

#endif //ANIMATION_COMPONENT_FACTORY_H