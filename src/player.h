#pragma once
#include <memory>
#include "entity.h"

class Player : public Entity
{
public:
	Player(
		std::shared_ptr<AnimationComponent> animationComponent,
		std::shared_ptr<MovementComponent> movementComponent,
		std::shared_ptr<HitboxComponent> hitboxComponent);
	virtual ~Player() = default;
	virtual void Update(Input in, float dt) const;
	virtual void Draw(sf::RenderTarget& target, float interp) const;

private:
	virtual void Update(float dt) const {};
	void InitPlayer() const;
	void SetAnimations() const;

	std::pair<int, int> spriteTextureSize;
	float spriteScale;
};
