#pragma once
#include <map>
#include <memory>

namespace sf {
	class Sprite;
	class Texture;
}

class Animation;

class AnimationComponent
{
public:
	AnimationComponent();
	virtual ~AnimationComponent();

	//Functions
	void SetAssets(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet);

	void AddAnimation(const int key, float frameDuration,
		int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);

	const bool& IsDone(const int key);
	const bool& Play(const int key, const bool priority = false);
	const bool& Play(const int key, const float& modifier, const float& modifierMax, const bool priority = false);

private:
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	std::map<const int, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
};
