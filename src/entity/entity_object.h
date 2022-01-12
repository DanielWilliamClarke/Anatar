#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "entity_update.h"

class IRenderer;
class IAnimationComponent;
class IHitboxComponent;
class ILocalMovementComponent;
class IWeaponComponent;
struct RayIntersection;

class EntityObject
{
public:
	EntityObject(
		std::shared_ptr<IAnimationComponent> animationComponent,
		std::shared_ptr<IHitboxComponent> hitboxComponent,
		std::shared_ptr<ILocalMovementComponent> movementComponent,
		std::shared_ptr<IWeaponComponent> weaponComponent);

	virtual ~EntityObject();
	
	void AddAnimation(const int key, float frameDuration, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);
	void PlayAnimation(const int direction, const bool loop) const;
	std::shared_ptr<sf::Sprite> GetSprite() const;

	void Update(EntityUpdate position, float dt) const;
	void Draw(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const;

	sf::FloatRect GetHitbox() const;

private:
	std::shared_ptr<IAnimationComponent> animationComponent;
	std::shared_ptr<IHitboxComponent> hitboxComponent;
	std::shared_ptr<ILocalMovementComponent> movementComponent;
	std::shared_ptr<IWeaponComponent> weaponComponent;

	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> texture;
};

#endif //ENTITY_OBJECT_H