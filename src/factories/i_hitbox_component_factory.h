#pragma once
#include <memory>

class HitboxComponent;

class IHitboxComponentFactory
{
public:
	IHitboxComponentFactory() = default;
	virtual ~IHitboxComponentFactory() = default;
	virtual std::shared_ptr<HitboxComponent> CreateInstance() = 0;
};