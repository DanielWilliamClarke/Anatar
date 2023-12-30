#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H


#include <SFML/Graphics.hpp>
#include <memory>

#include "entity_update.h"

class IRenderer;
class IAnimationComponent;
class IHitboxComponent;
class ILocalMovementComponent;
class IWeaponComponent;

class EntityObject
{
public:
	EntityObject(
		std::shared_ptr<IAnimationComponent> animationComponent,
		std::shared_ptr<IHitboxComponent> hitboxComponent,
		std::shared_ptr<ILocalMovementComponent> movementComponent,
		std::shared_ptr<IWeaponComponent> weaponComponent,
		std::shared_ptr<sf::Sprite> sprite);
	virtual ~EntityObject();
	
	void Update(EntityUpdate position, float dt) const;
	void Draw(std::shared_ptr<IRenderer> renderer, sf::Vector2f interPosition) const;

	std::shared_ptr<sf::Sprite> GetSprite() const;
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