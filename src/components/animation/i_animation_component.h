#ifndef I_ANIMATION_COMPONENT_H
#define I_ANIMATION_COMPONENT_H

#include <memory>

namespace sf {
	class Sprite;
	class Texture;
}

class IAnimationComponent
{
public:
	IAnimationComponent() = default;
	virtual ~IAnimationComponent() = default;

	virtual void SetAssets(std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> textureSheet) = 0;
	virtual void AddAnimation(const int key, float frameDuration,
		int startFrameX, int startFrameY, int framesX, int framesY, int width, int height) = 0;
	virtual const bool& IsDone(const int key) = 0;;
	virtual const bool& Play(const int key, const bool loop = true, const bool priority = false) = 0;;
	virtual const bool& Play(const int key, const float& modifier, const float& modifierMax, const bool loop = true, const bool priority = false) = 0;;
};

#endif // I_ANIMATION_COMPONENT_H