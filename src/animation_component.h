#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class Animation;

class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	void AddAnimation(const int key,
		float frameDuration,
		int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);

	const bool& IsDone(const int key);
	const bool& Play(const int key, const bool priority = false);
	const bool& Play(const int, const float& modifier, const float& modifierMax, const bool priority = false);

private:
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<const int, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
};
