#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <unordered_map>
#include <memory>

#include "i_animation_component.h"

namespace sf
{
	class Sprite;
	class Texture;
}

class Animation;

class AnimationComponent: public IAnimationComponent
{
public:
	AnimationComponent();
	~AnimationComponent() override = default;

	//Functions
	void SetAssets(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet) override;

	void AddAnimation(int key, float frameDuration,
		int startFrameX, int startFrameY, int framesX, int framesY, int width, int height) override;

    bool IsDone(int key) override;
	virtual bool Play(int key, bool loop = true, bool priority = false) override;
	virtual bool Play(int key, float modifier, float modifierMax, bool loop = true, bool priority = false) override;
	
private:
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	std::unordered_map<int, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
};

#endif