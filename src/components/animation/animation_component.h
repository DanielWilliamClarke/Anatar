#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#pragma once
#include <map>
#include <memory>

#include "i_animation_component.h"

namespace sf {
	class Sprite;
	class Texture;
}

class Animation;

class AnimationComponent: public IAnimationComponent
{
public:
	AnimationComponent();
	virtual ~AnimationComponent() = default;

	//Functions
	virtual void SetAssets(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet);

	virtual void AddAnimation(const int key, float frameDuration,
		int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);

	virtual const bool& IsDone(const int key);
	virtual const bool& Play(const int key, const bool loop = true, const bool priority = false);
	virtual const bool& Play(const int key, const float& modifier, const float& modifierMax, const bool loop = true, const bool priority = false);
	
private:
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	std::map<const int, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
};

#endif //ANIMATION_COMPONENT_H