#pragma once
#include <SFML/Graphics.hpp>

#include "entity_update.h"

class IAnimationComponentFactory;
class AnimationComponent;
class IHitboxComponentFactory;
class HitboxComponent;

class EntityObject
{
public:

	EntityObject(
		std::shared_ptr<IAnimationComponentFactory> animationComponentFactory,
		std::shared_ptr<IHitboxComponentFactory> hitboxComponentFactory);

	virtual ~EntityObject() = default;

	
	void SetPositionOffect(sf::Vector2f offset);
	void SetTexture(std::shared_ptr<sf::Texture> texture) const;
	void InitAnimationComponent(std::shared_ptr<sf::Texture> texture);
	void InitHitboxComponent(float offsetX, float offsetY, float width, float height);

	void AddAnimation(const int key, float frameDuration, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);
	std::shared_ptr<sf::Sprite> GetSprite() const;

	void Update(EntityUpdate position, float dt) const;
	void Draw(sf::RenderTarget& target, sf::Vector2f interPosition) const;

private:
	std::shared_ptr<IAnimationComponentFactory> animationComponentFactory;
	std::shared_ptr<AnimationComponent> animationComponent;

	std::shared_ptr<IHitboxComponentFactory> hitboxComponentFactory;
	std::shared_ptr<HitboxComponent> hitboxComponent;

	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> texture;
	sf::Vector2f positionOffset;
};