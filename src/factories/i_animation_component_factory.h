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