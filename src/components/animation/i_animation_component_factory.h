#ifndef I_ANIMATION_COMPONENT_FACTORY_H
#define I_ANIMATION_COMPONENT_FACTORY_H

#pragma once
#include <memory>

class AnimationComponent;

class IAnimationComponentFactory
{
public:
	IAnimationComponentFactory() = default;
	virtual ~IAnimationComponentFactory() = default;
	virtual std::shared_ptr<AnimationComponent> CreateInstance() = 0;
};

#endif // I_ANIMATION_COMPONENT_FACTORY_H